#include "game.h"
#include "assets.h"
#include "audio.h"
#include "camera.h"
#include "config.h"
#include "cursor.h"
#include "menu.h"
#include "pause_menu.h"
#include "renderer.h"
#include "settings.h"
#include "world.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdio.h>

void init_game(Game *game)
{
  InitAudioDevice();
  load_menu_music(game);
  load_playing_music(game);

  game->font = LoadFontEx("../assets/fonts/static/EBGaramond-Medium.ttf", FONT_SIZE, NULL, 0);
  game->menu.title_font = LoadFontEx("../assets/fonts/static/EBGaramond-Bold.ttf", MENU_TITLE_FONT_SIZE, NULL, 0);
  game->settings.font = LoadFontEx("../assets/fonts/static/EBGaramond-Medium.ttf", SETTINGS_FONT_SIZE, NULL, 0);

  game->should_exit = false;
  game->state = GAME_STATE_MENU;

  init_camera(&game->camera);
  init_menu(game);
  init_settings(game);
  load_settings(game);

  set_music_volume(&game->music, game->settings.options[SETTINGS_MUSIC_VOLUME].value);

  init_slider(&game->settings);
  init_pause_menu(game);

  load_world(&game->world);
  load_assets(&game->assets);
}

void update_game(Game *game)
{
  bool is_hovering = false;

  switch (game->state)
  {
    case GAME_STATE_MENU:
      if (game->overlay_state == OVERLAY_STATE_SETTINGS)
      {
        update_settings(game);
        is_hovering = is_hovering_settings(game);
      }
      else
      {
        update_menu(game);
        is_hovering = is_hovering_menu(game);
      }

      update_menu_music(game);
      break;

    case GAME_STATE_PLAYING:
    case GAME_STATE_PAUSED:
      if (game->overlay_state == OVERLAY_STATE_SETTINGS)
      {
        update_settings(game);
        is_hovering = is_hovering_settings(game);
      }
      else
      {
        update_pause_menu(game);
        is_hovering = is_hovering_pause_menu(game);
      }

      update_playing_music(game);
      break;
  }

  update_cursor(is_hovering);
}

void draw_current_state(Game *game)
{
  switch (game->state)
  {
    case GAME_STATE_MENU:
      draw_menu(game);

      if (game->overlay_state == OVERLAY_STATE_SETTINGS)
      {
        draw_settings(game);
      }
      break;

    case GAME_STATE_PLAYING:
    case GAME_STATE_PAUSED:
      BeginMode2D(game->camera);
      draw_game(game);
      EndMode3D();

      if (game->state == GAME_STATE_PAUSED)
      {
        draw_pause_menu(game);

        if (game->overlay_state == OVERLAY_STATE_SETTINGS)
        {
          draw_settings(game);
        }
      }
      break;
  }
}

void unload_game(Game *game)
{
  unload_assets(&game->assets);
  unload_music(game);

  TraceLog(LOG_INFO, "Game shutdown complete");
}
