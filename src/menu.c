#include "menu.h"
#include "button.h"
#include "config.h"
#include "cursor.h"
#include "game.h"
#include "settings.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stddef.h>

void init_menu(Game *game)
{
  PlayMusicStream(game->music.menu_music);

  game->menu.title = "Northhold";
  game->overlay_state = OVERLAY_STATE_NONE;
  // game->menu.background = LoadTexture("../assets/title/background.png");

  const float menu_width = 300;
  const float menu_height = 250;

  float rec_width = menu_width;
  const float rec_height = 50;
  const float rec_pos_x = ((float)GetScreenWidth() / 2.0F) - (rec_width / 2.0F);
  const float rec_pos_y = ((float)GetScreenHeight() / 2.0F) - (menu_height / 2.0F);

  float space_height = rec_height;

  const char *button_names[MENU_ITEM_COUNT] = {"Play", "Load", "Settings", "Exit"};

  for (int i = 0; i < MENU_ITEM_COUNT; i++)
  {
    Rectangle curr_outline = {
        rec_pos_x - BUTTON_OUTLINE_THICKNESS,
        rec_pos_y - BUTTON_OUTLINE_THICKNESS + (rec_height * (float)i) + (space_height * (float)i),
        rec_width + (BUTTON_OUTLINE_THICKNESS * 2),
        rec_height + (BUTTON_OUTLINE_THICKNESS * 2),
    };

    Rectangle curr_button_rec = {
        rec_pos_x,
        rec_pos_y + (rec_height * (float)i) + (space_height * (float)i),
        rec_width,
        rec_height,
    };

    game->menu.options[i] = (Button){
        curr_outline,         curr_button_rec, button_names[i],      false,
        BUTTON_OUTLINE_COLOR, BUTTON_COLOR,    BUTTON_COLOR_HOVERED, BUTTON_ROUNDNESS,
    };
  }
}

void update_menu(Game *game)
{
  Button *options = game->menu.options;

  switch (which_button_pressed(options, MENU_ITEM_COUNT))
  {
    case 0:
      game->state = GAME_STATE_PLAYING;
      SetMouseCursor(MOUSE_CURSOR_DEFAULT);
      StopMusicStream(game->music.menu_music);
      StopMusicStream(game->music.playing1_music);
      PlayMusicStream(game->music.playing1_music);
      break;
    case 1:
      break;
    case 2:
      open_settings(game);
      game->overlay_state = OVERLAY_STATE_SETTINGS;
      SetMouseCursor(MOUSE_CURSOR_DEFAULT);
      game->menu.options[2].is_hovered = false;
      break;
    case 3:
      game->should_exit = true;
      break;
    default:
      break;
  }
}

void draw_menu(Game *game)
{
  DrawTexture(game->menu.background, 0, 0, WHITE);

  Font font = game->font;
  const float h_align = 0.5F;
  const float v_align = 0.5F;
  const float title_spacing = (float)game->menu.title_font.baseSize * 0.01F;

  Vector2 title_size =
      MeasureTextEx(game->menu.title_font, game->menu.title, (float)game->menu.title_font.baseSize, title_spacing);

  const float title_x = ((float)GetScreenWidth() / 2.0F) - (title_size.x / 2.0F);
  const float title_y = 150.0F;
  Vector2 title_pos = (Vector2){title_x, title_y};

  DrawTextEx(game->menu.title_font, game->menu.title, title_pos, (float)game->menu.title_font.baseSize, title_spacing,
             BUTTON_TITLE_COLOR);

  Button *options = game->menu.options;

  for (int i = 0; i < MENU_ITEM_COUNT; i++)
  {
    Rectangle outline = options[i].outline;
    Rectangle rec = options[i].rec;
    const char *text = options[i].text;

    Color color = BUTTON_COLOR;

    if (options[i].is_hovered)
    {
      color = BUTTON_COLOR_HOVERED;
    }

    DrawRectangleRounded(outline, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, BUTTON_OUTLINE_COLOR);
    DrawRectangleRounded(rec, BUTTON_ROUNDNESS, BUTTON_SEGMENTS, color);

    Vector2 text_size = MeasureTextEx(font, text, (float)FONT_SIZE, TEXT_SPACING);

    Vector2 text_pos = (Vector2){
        rec.x + Lerp(0.0F, rec.width - text_size.x, h_align),
        rec.y + Lerp(0.0F, rec.height - text_size.y, v_align),
    };

    DrawTextEx(font, text, text_pos, FONT_SIZE, TEXT_SPACING, BUTTON_TEXT_COLOR);
  }
}
