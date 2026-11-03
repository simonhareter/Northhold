#include "pause_menu.h"
#include "button.h"
#include "config.h"
#include "cursor.h"
#include "game.h"

#include <raylib.h>
#include <raymath.h>
#include <stddef.h>

void init_pause_menu(Game *game)
{
  PauseMenu pause_menu;

  float menu_box_width = 400;
  float menu_box_height = 500;
  Rectangle menu_box = {SCREEN_WIDTH / 2.0f - menu_box_width / 2.0f, SCREEN_HEIGHT / 2.0f - menu_box_height / 2.0f,
                        menu_box_width, menu_box_height};

  pause_menu.menu_box = menu_box;

  float title_box_width = 200;
  float title_box_height = 50;
  Rectangle title_box = {SCREEN_WIDTH / 2.0f - title_box_width / 2.0f, menu_box.y - title_box_height / 2.0f,
                         title_box_width, title_box_height};

  pause_menu.title_box = title_box;
  pause_menu.pause_menu_title = "Game Menu";

  float rec_width = 300;
  float rec_height = 50;
  float rec_pos_x = SCREEN_WIDTH / 2.0f - rec_width / 2.0f;
  float rec_pos_y = SCREEN_HEIGHT / 2.0f - menu_box_height / 2.0f + rec_height * 1.5f;

  const char *button_names[PAUSE_MENU_COUNT] = {"Resume", "Save", "Settings", "Exit"};

  for (int i = 0; i < PAUSE_MENU_COUNT; i++)
  {
    Rectangle curr_outline = {rec_pos_x - BUTTON_OUTLINE_THICKNESS,
                              rec_pos_y - BUTTON_OUTLINE_THICKNESS + rec_height * (i * 2),
                              rec_width + BUTTON_OUTLINE_THICKNESS * 2, rec_height + BUTTON_OUTLINE_THICKNESS * 2};
    Rectangle curr_button_rec = {rec_pos_x, rec_pos_y + rec_height * (i * 2), rec_width, rec_height};
    pause_menu.options[i] = (Button){curr_outline, curr_button_rec, button_names[i]};
  }

  game->pause_menu = pause_menu;
}

void update_pause_menu(Game *game)
{
  Button *options = game->pause_menu.options;
  bool hovering_button = is_mouse_over_any_button(options, PAUSE_MENU_COUNT);
  update_cursor(hovering_button);

  switch (which_button_pressed(options, PAUSE_MENU_COUNT))
  {
    case 0:
      game->state = GAME_STATE_PLAYING;
      break;
    case 1:
      game->state = GAME_STATE_PLAYING;
      TraceLog(LOG_INFO, "Saving the game is not yet implemented");
      break;
    case 2:
      game->state = GAME_STATE_SETTINGS;
      break;
    case 3:
      StopMusicStream(game->menu_music);
      PlayMusicStream(game->menu_music);
      game->state = GAME_STATE_MENU;
      break;
    default:
      return;
      break;
  }

  SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}

void draw_pause_menu(Game *game)
{
  // BOX
  Font font = game->font;
  float spacing = FONT_SIZE * 0.1;
  float h_align = 0.5, v_align = 0.5;

  DrawRectangleRec(game->pause_menu.menu_box, Fade(BLACK, 0.8f));

  // TITLE
  DrawRectangleRec(game->pause_menu.title_box, BUTTON_TITLE_COLOR);

  const char *title_text = game->pause_menu.pause_menu_title;
  Rectangle title_rec = game->pause_menu.title_box;
  Vector2 title_size = MeasureTextEx(font, title_text, FONT_SIZE, spacing);
  Vector2 title_pos = (Vector2){title_rec.x + Lerp(0.0f, title_rec.width - title_size.x, h_align),
                                title_rec.y + Lerp(0.0f, title_rec.height - title_size.y, v_align)};

  DrawTextEx(font, game->pause_menu.pause_menu_title, title_pos, FONT_SIZE, spacing, BUTTON_TITLE_TEXT_COLOR);

  // PAUSE MENU OPTIONS
  for (int i = 0; i < PAUSE_MENU_COUNT; i++)
  {
    Rectangle rec = game->pause_menu.options[i].rec;
    const char *text = game->pause_menu.options[i].text;

    DrawRectangleRec(rec, BUTTON_COLOR);

    Vector2 text_size = MeasureTextEx(font, text, FONT_SIZE, spacing);
    Vector2 text_pos = (Vector2){rec.x + Lerp(0.0f, rec.width - text_size.x, h_align),
                                 rec.y + Lerp(0.0f, rec.height - text_size.y, v_align)};

    DrawTextEx(font, text, text_pos, FONT_SIZE, spacing, BUTTON_TEXT_COLOR);
  }
}
