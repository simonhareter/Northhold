#include "game.h"
#include "assets.h"
#include "audio.h"
#include "config.h"
#include "menu.h"
#include "pause_menu.h"
#include "renderer.h"
#include "settings.h"
#include "world.h"
#include <raylib.h>
#include <stdio.h>

void init_game(Game *game)
{
  InitAudioDevice();
  load_menu_music(game);

  game->font = LoadFontEx("../assets/fonts/static/EBGaramond-Medium.ttf", FONT_SIZE, NULL, 0);
  game->menu.title_font = LoadFontEx("../assets/fonts/static/EBGaramond-Bold.ttf", MENU_TITLE_FONT_SIZE, NULL, 0);
  game->settings.font = LoadFontEx("../assets/fonts/static/EBGaramond-Medium.ttf", SETTINGS_FONT_SIZE, NULL, 0);

  game->should_exit = false;
  game->state = GAME_STATE_MENU;
  game->camera = (Camera2D){.target = {WORLD_WIDTH * TILE_SIZE / 2.0f, WORLD_HEIGHT * TILE_SIZE / 2.0f},
                            .offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
                            .rotation = 0.0f,
                            .zoom = 1.0f};

  init_menu(game);
  init_settings(game);
  load_settings(game);

  SetMusicVolume(game->menu_music, game->settings.options[SETTINGS_MUSIC_VOLUME].value / 100.0f);

  init_slider(&game->settings);
  init_pause_menu(game);

  load_world(&game->world);
  load_assets(&game->assets);
}

void update_game(Game *game)
{
  switch (game->state)
  {
    case GAME_STATE_MENU:
      update_menu(game);
      update_menu_music(game);
      break;
    case GAME_STATE_PLAYING:
      break;
    case GAME_STATE_PAUSED:
      update_pause_menu(game);
      break;
    case GAME_STATE_SETTINGS:
      update_settings(game);
      update_menu_music(game);
      break;
  }
}

void draw_current_state(Game *game)
{
  switch (game->state)
  {
    case GAME_STATE_MENU:
    case GAME_STATE_SETTINGS:
      draw_menu(game);

      if (game->state == GAME_STATE_SETTINGS)
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
