#include "settings.h"
#include "button.h"
#include "config.h"
#include "cursor.h"
#include "game.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

void init_settings(Game *game)
{
  const float center_x = SCREEN_WIDTH / 2.0f;
  const float center_y = SCREEN_HEIGHT / 2.0f;

  const float box_width = 700.0f;
  const float box_height = 650.0f;

  const float title_width = 300.0f;
  const float button_width = 150.0f;
  const float button_height = 50.0f;
  const float button_margin = 150.0f;

  const char *button_names[SETTINGS_UI_ELEMENTS_COUNT] = {"", "Settings", "Cancel", "Save"};

  const Color button_outline_color[SETTINGS_UI_ELEMENTS_COUNT] = {
      Fade(BUTTON_OUTLINE_COLOR, BOX_OPACITY), BUTTON_OUTLINE_COLOR, BUTTON_OUTLINE_COLOR, BUTTON_OUTLINE_COLOR};

  const Color button_color[SETTINGS_UI_ELEMENTS_COUNT] = {Fade(BLACK, BOX_OPACITY), BUTTON_TITLE_COLOR,
                                                          BUTTON_TITLE_COLOR, BUTTON_COLOR};

  Rectangle rects[SETTINGS_UI_ELEMENTS_COUNT] = {
      [BOX] = {center_x - box_width / 2.0f, center_y - box_height / 2.0f, box_width, box_height},
      [TITLE] = {center_x - title_width / 2.0f, center_y - box_height / 2.0f - button_height / 2.0f, title_width,
                 button_height},
      [CANCEL] = {center_x - button_width / 2.0f - button_margin, center_y + box_height / 2.0f - button_height * 1.5f,
                  button_width, button_height},
      [SAVE] = {center_x - button_width / 2.0f + button_margin, center_y + box_height / 2.0f - button_height * 1.5f,
                button_width, button_height}};

  for (int i = 0; i < SETTINGS_UI_ELEMENTS_COUNT; i++)
  {
    float roundness = (i == BOX) ? MENU_ROUNDNESS : BUTTON_ROUNDNESS;

    Rectangle outline = {rects[i].x - BUTTON_OUTLINE_THICKNESS, rects[i].y - BUTTON_OUTLINE_THICKNESS,
                         rects[i].width + BUTTON_OUTLINE_THICKNESS * 2, rects[i].height + BUTTON_OUTLINE_THICKNESS * 2};

    game->settings.ui_elements[i] =
        (Button){outline, rects[i], button_names[i], false, button_outline_color[i], button_color[i], roundness};
  }

  const char *option_names[SETTINGS_COUNT] = {"Music Volume", "Test Option1", "Test Option4", "Test Option3"};
  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    Setting option = {option_names[i], 50};
    game->settings.options[i] = option;
  }
}

void update_settings(Game *game)
{
  // putting pointer to 3rd element (only 3rd and 4th are actually buttons to click)
  Button *buttons = &game->settings.ui_elements[2];
  const int BUTTON_COUNT = 2;
  bool hovering_button = is_mouse_over_any_button(buttons, BUTTON_COUNT);
  update_cursor(hovering_button);

  // 3 -> 0, 4 -> 1
  switch (which_button_pressed(buttons, SETTINGS_UI_ELEMENTS_COUNT))
  {
    case 0:
      game->state = GAME_STATE_MENU;
      TraceLog(LOG_INFO, "didnt save settings");
      break;
    case 1:
      game->state = GAME_STATE_MENU;
      TraceLog(LOG_INFO, "saved settings");
      break;
    default:
      break;
  }
}

void draw_settings(Game *game)
{
  for (int i = 0; i < SETTINGS_UI_ELEMENTS_COUNT; i++)
  {
    Rectangle outline = game->settings.ui_elements[i].outline;
    Rectangle button = game->settings.ui_elements[i].rec;
    float roundness = game->settings.ui_elements[i].roundness;
    Color outline_color = game->settings.ui_elements[i].outline_color;
    Color rec_color = game->settings.ui_elements[i].rec_color;

    if (i >= 2 && game->settings.ui_elements[i].is_hovered)
    {
      rec_color = (i == SAVE) ? BUTTON_COLOR_HOVERED : BUTTON_TITLE_COLOR_HOVERED;
    }

    DrawRectangleRounded(outline, roundness, BUTTON_SEGMENTS, outline_color);
    DrawRectangleRounded(button, roundness, BUTTON_SEGMENTS, rec_color);

    const char *text = game->settings.ui_elements[i].text;
    Vector2 text_size = MeasureTextEx(game->font, text, FONT_SIZE, TEXT_SPACING);
    Vector2 text_pos = (Vector2){button.x + Lerp(0.0f, button.width - text_size.x, H_ALIGN),
                                 button.y + Lerp(0.0f, button.height - text_size.y, V_ALIGN)};

    DrawTextEx(game->font, text, text_pos, FONT_SIZE, TEXT_SPACING, BUTTON_TEXT_COLOR);
  }

  float box_height = game->settings.ui_elements[0].rec.height;
  float rec_height = game->settings.ui_elements[TITLE].rec.height;
  float option_height = SCREEN_HEIGHT / 2.0f - box_height / 2.0f + rec_height * 2.0f;
  float option_start_pos = SCREEN_WIDTH / 2.0f - 300.0f;
  float option_bar_start_pos = option_start_pos + 200;
  float option_bar_width = SCREEN_WIDTH * 0.15625;

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    DrawTextEx(game->settings.font, game->settings.options[i].name,
               (Vector2){option_start_pos, option_height + i * rec_height}, SETTINGS_FONT_SIZE, TEXT_SPACING,
               BUTTON_TEXT_COLOR);

    DrawLine(option_bar_start_pos, option_height + i * rec_height + 16, option_bar_start_pos + option_bar_width,
             option_height + i * rec_height + 16, BUTTON_TITLE_COLOR);

    DrawTextEx(game->settings.font, TextFormat("%d%%", game->settings.options[i].value),
               (Vector2){option_start_pos + option_bar_width + 250, option_height + i * rec_height}, SETTINGS_FONT_SIZE,
               TEXT_SPACING, BUTTON_TEXT_COLOR);
  }
}
