#include "settings.h"
#include "button.h"
#include "config.h"
#include "cursor.h"
#include "game.h"
#include "slider.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void init_settings(Game *game)
{
  const float center_x = SCREEN_WIDTH / 2.0f;
  const float center_y = SCREEN_HEIGHT / 2.0f;

  const float box_width = 800.0f;
  const float box_height = 650.0f;

  const float title_width = 300.0f;
  const float button_width = 150.0f;
  const float button_height = 50.0f;
  const float button_margin = 150.0f;

  const char *ui_button_names[SETTINGS_UI_ELEMENTS_COUNT] = {"", "Settings"};
  const char *button_names[SETTINGS_BUTTON_COUNT] = {"Cancel", "Save"};

  const Color ui_button_outline_color[SETTINGS_UI_ELEMENTS_COUNT] = {Fade(BUTTON_OUTLINE_COLOR, BOX_OPACITY),
                                                                     BUTTON_OUTLINE_COLOR};
  const Color button_outline_color[SETTINGS_BUTTON_COUNT] = {BUTTON_OUTLINE_COLOR, BUTTON_OUTLINE_COLOR};

  const Color ui_button_color[SETTINGS_UI_ELEMENTS_COUNT] = {Fade(BLACK, BOX_OPACITY), BUTTON_TITLE_COLOR};
  const Color button_color[SETTINGS_BUTTON_COUNT] = {BUTTON_TITLE_COLOR, BUTTON_COLOR};

  Rectangle ui_buttons[SETTINGS_UI_ELEMENTS_COUNT] = {
      [BOX] = {center_x - box_width / 2.0f, center_y - box_height / 2.0f, box_width, box_height},
      [TITLE] = {center_x - title_width / 2.0f, center_y - box_height / 2.0f - button_height / 2.0f, title_width,
                 button_height},
  };

  Rectangle buttons[SETTINGS_BUTTON_COUNT] = {
      [CANCEL] = {center_x - button_width / 2.0f - button_margin, center_y + box_height / 2.0f - button_height * 1.5f,
                  button_width, button_height},
      [SAVE] = {center_x - button_width / 2.0f + button_margin, center_y + box_height / 2.0f - button_height * 1.5f,
                button_width, button_height}};

  for (int i = 0; i < SETTINGS_UI_ELEMENTS_COUNT; i++)
  {
    float roundness = (i == BOX) ? MENU_ROUNDNESS : BUTTON_ROUNDNESS;

    Rectangle outline = {ui_buttons[i].x - BUTTON_OUTLINE_THICKNESS, ui_buttons[i].y - BUTTON_OUTLINE_THICKNESS,
                         ui_buttons[i].width + BUTTON_OUTLINE_THICKNESS * 2,
                         ui_buttons[i].height + BUTTON_OUTLINE_THICKNESS * 2};

    game->settings.ui_elements[i] = (Button){outline,
                                             ui_buttons[i],
                                             ui_button_names[i],
                                             false,
                                             ui_button_outline_color[i],
                                             ui_button_color[i],
                                             BUTTON_TITLE_COLOR_HOVERED,
                                             roundness};
  }

  for (int i = 0; i < SETTINGS_BUTTON_COUNT; i++)
  {
    Rectangle outline = {buttons[i].x - BUTTON_OUTLINE_THICKNESS, buttons[i].y - BUTTON_OUTLINE_THICKNESS,
                         buttons[i].width + BUTTON_OUTLINE_THICKNESS * 2,
                         buttons[i].height + BUTTON_OUTLINE_THICKNESS * 2};

    Color hovered_color = i == CANCEL ? BUTTON_TITLE_COLOR_HOVERED : BUTTON_COLOR_HOVERED;

    game->settings.buttons[i] =
        (Button){outline,         buttons[i],    button_names[i], false, button_outline_color[i],
                 button_color[i], hovered_color, BUTTON_ROUNDNESS};
  }

  const char *option_names[SETTINGS_COUNT] = {"Music Volume"};

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    Setting option = {
        .name = option_names[i], .value = 50, .min_value = 0, .max_value = 100, .slider = {.line = {0}, .knob = {0}}};
    game->settings.options[i] = option;
  }

  create_settings(game);
}

// XDG_CONFIG_HOME = /home/.config/
// XDG_DATA_HOME = /home/.local/share/
void create_settings(Game *game)
{
  const char *base = getenv("XDG_CONFIG_HOME");

  if (base == NULL || base[0] == '\0')
  {
    const char *home = getenv("HOME");

    if (home == NULL)
    {
      TraceLog(LOG_ERROR, "HOME is not set");
      return;
    }
    base = TextFormat("%s/.config", home);
  }

  const char *directory = TextFormat("%s/Northhold", base);

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
  const char *config_home = getenv("XDG_CONFIG_HOME");

  FILE *fptr = fopen(TextFormat("%s/Northhold/settings.txt", config_home), "r");
  int size = 25;
  char line[size];

  if (fptr == NULL)
  {
    TraceLog(LOG_ERROR, "Not able to open the settings.txt file");
    return;
  }

  int i = 0, equals = 61;
  int start = 0;
  char value_char[4];

  while (fgets(line, size, fptr))
  {
    for (int j = 0; j < size; j++)
    {
      if (line[j] == equals)
      {
        j++;
        continue;
      }

      if (line[j] >= 48 && line[j] <= 57 && start <= 2)
      {
        printf("%c\n", line[j]);
        value_char[start] = line[j];
        start++;
      }
    }
    value_char[start] = '\0';
    game->settings.options[i].value = atoi(value_char);
    i++;
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

  SetMusicVolume(game->music.menu_music, game->settings.options[SETTINGS_MUSIC_VOLUME].value / 100.0f);
  SetMusicVolume(game->music.playing1_music, game->settings.options[SETTINGS_MUSIC_VOLUME].value / 100.0f);

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
    Vector2 text_pos = (Vector2){button.x + Lerp(0.0f, button.width - text_size.x, H_ALIGN),
                                 button.y + Lerp(0.0f, button.height - text_size.y, V_ALIGN)};

    DrawTextEx(*font, text, text_pos, FONT_SIZE, TEXT_SPACING, BUTTON_TEXT_COLOR);
  }
}

void draw_options(Game *game)
{
  float padding = 50;
  float gap = 40;

  Rectangle box = game->settings.ui_elements[BOX].rec;
  Rectangle rec = game->settings.ui_elements[TITLE].rec;

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    const char *name = game->settings.options[i].name;
    const char *value = TextFormat("%d", game->settings.options[i].value);

    Vector2 option_pos = {box.x + padding, box.y + rec.height * i + padding};

    Setting *option = &game->settings.options[i];

    float value_x = option->slider.line.x + option->slider.line.width + gap;
    Vector2 value_pos = {value_x, box.y + rec.height * i + padding};

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
  const char *config_home = getenv("XDG_CONFIG_HOME");

  FILE *fptr = fopen(TextFormat("%s/Northhold/settings.txt", config_home), "w");

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
