#include "settings.h"
#include "audio.h"
#include "button.h"
#include "config.h"
#include "cursor.h"
#include "game.h"
#include "slider.h"
#include <errno.h>
#include <limits.h>
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void init_settings(Game *game)
{
  const float screen_center_x = (float)GetScreenWidth() / 2.0F;
  const float screen_center_y = (float)GetScreenHeight() / 2.0F;

  const float box_width = 800.0F;
  const float box_height = 650.0F;

  const float title_width = 300.0F;
  const float button_width = 150.0F;
  const float button_height = 50.0F;
  const float button_margin = 150.0F;

  const float box_x = screen_center_x - (box_width / 2.0F);
  const float box_y = screen_center_y - (box_height / 2.0F);

  const float title_x = screen_center_x - (title_width / 2.0F);
  const float title_y = screen_center_y - (box_height / 2.0F) - (button_height / 2.0F);

  Rectangle ui_buttons[SETTINGS_UI_ELEMENTS_COUNT] = {
      [BOX] =
          {
              box_x,
              box_y,
              box_width,
              box_height,
          },
      [TITLE] =
          {
              title_x,
              title_y,
              title_width,
              button_height,
          },
  };

  const float cancel_x = screen_center_x - (button_width / 2.0F) - button_margin;
  const float cancel_y = screen_center_y + (box_height / 2.0F) - (button_height * 1.5F);

  const float play_x = screen_center_x - (button_width / 2.0F) + button_margin;
  const float play_y = screen_center_y + (box_height / 2.0F) - (button_height * 1.5F);

  Rectangle buttons[SETTINGS_BUTTON_COUNT] = {
      [CANCEL] =
          {
              cancel_x,
              cancel_y,
              button_width,
              button_height,
          },
      [SAVE] =
          {
              play_x,
              play_y,
              button_width,
              button_height,
          },
  };

  const char *ui_button_names[SETTINGS_UI_ELEMENTS_COUNT] = {"", "Settings"};
  const char *button_names[SETTINGS_BUTTON_COUNT] = {"Cancel", "Save"};

  const Color ui_button_outline_color[SETTINGS_UI_ELEMENTS_COUNT] = {
      Fade(BUTTON_OUTLINE_COLOR, BOX_OPACITY),
      BUTTON_OUTLINE_COLOR,
  };
  const Color button_outline_color[SETTINGS_BUTTON_COUNT] = {BUTTON_OUTLINE_COLOR, BUTTON_OUTLINE_COLOR};

  const Color ui_button_color[SETTINGS_UI_ELEMENTS_COUNT] = {Fade(BLACK, BOX_OPACITY), BUTTON_TITLE_COLOR};
  const Color button_color[SETTINGS_BUTTON_COUNT] = {BUTTON_TITLE_COLOR, BUTTON_COLOR};

  for (int i = 0; i < SETTINGS_UI_ELEMENTS_COUNT; i++)
  {
    float roundness = (i == BOX) ? MENU_ROUNDNESS : BUTTON_ROUNDNESS;

    Rectangle outline = {
        ui_buttons[i].x - BUTTON_OUTLINE_THICKNESS,
        ui_buttons[i].y - BUTTON_OUTLINE_THICKNESS,
        ui_buttons[i].width + (BUTTON_OUTLINE_THICKNESS * 2),
        ui_buttons[i].height + (BUTTON_OUTLINE_THICKNESS * 2),
    };

    game->settings.ui_elements[i] = (Button){
        outline,
        ui_buttons[i],
        ui_button_names[i],
        false,
        ui_button_outline_color[i],
        ui_button_color[i],
        BUTTON_TITLE_COLOR_HOVERED,
        roundness,
    };
  }

  for (int i = 0; i < SETTINGS_BUTTON_COUNT; i++)
  {
    Rectangle outline = {
        buttons[i].x - BUTTON_OUTLINE_THICKNESS,
        buttons[i].y - BUTTON_OUTLINE_THICKNESS,
        buttons[i].width + (BUTTON_OUTLINE_THICKNESS * 2),
        buttons[i].height + (BUTTON_OUTLINE_THICKNESS * 2),
    };

    Color hovered_color = i == CANCEL ? BUTTON_TITLE_COLOR_HOVERED : BUTTON_COLOR_HOVERED;

    game->settings.buttons[i] = (Button){
        outline,         buttons[i],    button_names[i],  false, button_outline_color[i],
        button_color[i], hovered_color, BUTTON_ROUNDNESS,
    };
  }

  const char *option_names[SETTINGS_COUNT] = {"Music Volume"};

  const int default_volume = 50;
  const int min_volume = 0;
  const int max_volume = 100;

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    Setting option = {
        .name = option_names[i],
        .value = default_volume,
        .min_value = min_volume,
        .max_value = max_volume,
        .slider = {.line = {0}, .knob = {0}},
    };
    game->settings.options[i] = option;
  }

  create_settings(game);
}

// XDG_CONFIG_HOME = /home/.config/
// XDG_DATA_HOME = /home/.local/share/
void create_settings(Game *game)
{
  const char *base = getenv("HOME");

  if (base == NULL)
  {
    TraceLog(LOG_ERROR, "HOME is not set");
    return;
  }

  const char *directory = TextFormat("%s/.config/Northhold", base);

  if (MakeDirectory(directory) != 0 && !DirectoryExists(directory))
  {
    TraceLog(LOG_ERROR, "Failed to create settings directory");
    return;
  }

  const char *path = TextFormat("%s/settings.txt", directory);

  if (FileExists(path))
  {
    return;
  }

  FILE *fptr = fopen(path, "w");

  if (fptr == NULL)
  {
    TraceLog(LOG_ERROR, "Failed to open settings file: %s", path);
    return;
  }

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    Setting option = game->settings.options[i];

    fprintf(fptr, "%s = %d\n", option.name, option.value);
  }
  fclose(fptr);
}

void load_settings(Game *game)
{
  const char *config_home = getenv("HOME");

  FILE *fptr = fopen(TextFormat("%s/.config/Northhold/settings.txt", config_home), "r");

  const int size = 25;
  char line[size];

  if (fptr == NULL)
  {
    TraceLog(LOG_ERROR, "Not able to open the settings.txt file");
    return;
  }

  int setting_idx = 0;
  int start = 0;
  char value_char[4];

  while (fgets(line, size, fptr))
  {
    for (int j = 0; line[j] != '\0'; j++)
    {
      if (line[j] == KEY_EQUAL)
      {
        j++;
        continue;
      }

      if (line[j] >= KEY_ZERO && line[j] <= KEY_NINE && start <= 2)
      {
        printf("%c\n", line[j]);
        value_char[start] = line[j];
        start++;
      }
    }

    value_char[start] = '\0';

    char *endptr;
    errno = 0;

    const int base_ten = 10;
    long value = strtol(value_char, &endptr, base_ten);

    if (endptr == value_char || *endptr != '\0' || errno == ERANGE || value < INT_MIN || value > INT_MAX)
    {
      start = 0;
      continue;
    }

    game->settings.options[setting_idx].value = (int)value;

    setting_idx++;
    start = 0;
  }

  fclose(fptr);
}

void update_settings(Game *game)
{
  // putting pointer to 2nd element (only 2nd and 3rd are clickable buttons. at some point might be a good idea to
  // seperate clickable and non-clickbale ui elements)
  Button *buttons = &game->settings.buttons[0];

  update_slider(&game->settings);

  set_music_volume(&game->music, game->settings.options[SETTINGS_MUSIC_VOLUME].value);

  // 3 -> 0, 4 -> 1
  switch (which_button_pressed(buttons, SETTINGS_BUTTON_COUNT))
  {
    case 0:
      game->overlay_state = OVERLAY_STATE_NONE;
      cancel_settings(game);
      TraceLog(LOG_INFO, "didnt save settings");
      break;
    case 1:
      game->overlay_state = OVERLAY_STATE_NONE;
      save_settings(game);
      TraceLog(LOG_INFO, "saved settings");
      break;
    default:
      break;
  }
}

void draw_settings(Game *game)
{
  draw_ui_elements(game->settings.ui_elements, SETTINGS_UI_ELEMENTS_COUNT, &game->font);
  draw_ui_elements(game->settings.buttons, SETTINGS_BUTTON_COUNT, &game->font);
  draw_options(game);
}

void draw_ui_elements(Button *elements, int element_count, Font *font)
{
  if (font == NULL)
  {
    TraceLog(LOG_ERROR, "Font pointer is NULL!");
    return;
  }

  for (int i = 0; i < element_count; i++)
  {
    Rectangle outline = elements[i].outline;
    Rectangle button = elements[i].rec;
    float roundness = elements[i].roundness;
    Color outline_color = elements[i].outline_color;
    Color rec_color = elements[i].rec_color;

    if (elements[i].is_hovered)
    {
      rec_color = elements[i].hovered_color;
    }

    DrawRectangleRounded(outline, roundness, BUTTON_SEGMENTS, outline_color);
    DrawRectangleRounded(button, roundness, BUTTON_SEGMENTS, rec_color);

    const char *text = elements[i].text;

    Vector2 text_size = MeasureTextEx(*font, text, FONT_SIZE, TEXT_SPACING);
    Vector2 text_pos = (Vector2){
        button.x + Lerp(0.0F, button.width - text_size.x, H_ALIGN),
        button.y + Lerp(0.0F, button.height - text_size.y, V_ALIGN),
    };

    DrawTextEx(*font, text, text_pos, FONT_SIZE, TEXT_SPACING, BUTTON_TEXT_COLOR);
  }
}

void draw_options(Game *game)
{
  const float padding = 50;
  const float gap = 40;

  Rectangle box = game->settings.ui_elements[BOX].rec;
  Rectangle rec = game->settings.ui_elements[TITLE].rec;

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    const char *name = game->settings.options[i].name;
    const char *value = TextFormat("%d", game->settings.options[i].value);

    Vector2 option_pos = {box.x + padding, box.y + (rec.height * (float)i) + padding};

    Setting *option = &game->settings.options[i];

    float value_x = option->slider.line.x + option->slider.line.width + gap;
    Vector2 value_pos = {value_x, box.y + (rec.height * (float)i) + padding};

    DrawTextEx(game->settings.font, name, option_pos, SETTINGS_FONT_SIZE, TEXT_SPACING, BUTTON_TEXT_COLOR);
    DrawTextEx(game->settings.font, value, value_pos, SETTINGS_FONT_SIZE, TEXT_SPACING, BUTTON_TEXT_COLOR);
  }
  draw_slider(&game->settings);
}

void open_settings(Game *game)
{
  Settings *settings = &game->settings;

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    settings->original_options[i] = settings->options[i];
  }
}

void cancel_settings(Game *game)
{
  Settings *settings = &game->settings;

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    settings->options[i] = settings->original_options[i];
  }
}

void save_settings(Game *game)
{
  const char *config_home = getenv("HOME");

  FILE *fptr = fopen(TextFormat("%s/.config/Northhold/settings.txt", config_home), "w");

  if (fptr == NULL)
  {
    TraceLog(LOG_ERROR, "Failed to open settings file.");
    return;
  }

  Settings *settings = &game->settings;

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    Setting *option = &settings->options[i];
    fprintf(fptr, "%s = %d\n", option->name, option->value);
  }

  fclose(fptr);
}
