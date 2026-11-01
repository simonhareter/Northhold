#include "menu.h"
#include "button.h"
#include "config.h"
#include "cursor.h"
#include "game.h"
#include <raylib.h>
#include <raymath.h>
#include <stddef.h>

void init_menu(Game *game)
{
  float menu_width = 300;
  float menu_height = 250;

  float rec_width = menu_width;
  float rec_height = 50;
  float rec_pos_x = SCREEN_WIDTH / 2.0f - rec_width / 2.0f;
  float rec_pos_y = SCREEN_HEIGHT / 2.0f - menu_height / 2.0f;

  float space_height = rec_height;

  game->menu.options[0] = (Button){{rec_pos_x, rec_pos_y, rec_width, rec_height}, "Play"};
  game->menu.options[1] =
      (Button){{rec_pos_x, rec_pos_y + rec_height + space_height, rec_width, rec_height}, "Settings"};
  game->menu.options[2] =
      (Button){{rec_pos_x, rec_pos_y + rec_height * 2 + space_height * 2, rec_width, rec_height}, "Exit"};
  game->menu.option_count = 3;
}

void update_menu(Game *game)
{
  size_t size = sizeof(game->menu.options) / sizeof(game->menu.options[0]);
  bool hovering_button = is_mouse_over_any_button(game->menu.options, size);
  update_cursor(hovering_button);

  switch (which_button_pressed(game->menu.options, size))
  {
    case 0:
      game->state = GAME_STATE_PLAYING;
      SetMouseCursor(MOUSE_CURSOR_DEFAULT);
      break;
    case 1:
      game->state = GAME_STATE_SETTINGS;
      break;
    case 2:
      game->should_exit = true;
      break;
  }
}

void draw_menu(Game *game)
{
  Font font = game->font;
  float font_size = 30;
  float spacing = font_size * 0.1;
  float h_align = 0.5, v_align = 0.5;

  Button *options = game->menu.options;
  int size = game->menu.option_count;

  for (int i = 0; i < size; i++)
  {
    Rectangle rec = options[i].rec;
    const char *text = options[i].text;

    DrawRectangleRec(rec, BLUE);

    Vector2 text_size = MeasureTextEx(font, text, (float)font_size, spacing);
    Vector2 text_pos = (Vector2){rec.x + Lerp(0.0f, rec.width - text_size.x, h_align),
                                 rec.y + Lerp(0.0f, rec.height - text_size.y, v_align)};

    DrawTextEx(font, text, text_pos, font_size, spacing, BLACK);
  }
}
