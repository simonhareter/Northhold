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

void init_game(Game *game)
{
  InitAudioDevice();
  play_menu_music(game);

  init_menu(game);
  init_pause_menu(game);
  game->should_exit = false;
  game->state = GAME_STATE_MENU;
  game->camera = (Camera2D){.target = {WORLD_WIDTH * TILE_SIZE / 2.0f, WORLD_HEIGHT * TILE_SIZE / 2.0f},
                            .offset = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f},
                            .rotation = 0.0f,
                            .zoom = 1.0f};

  game->font = GetFontDefault();

  load_world(&game->world);
  load_assets(&game->assets);
}

void update_game(Game *game)
{
  switch (game->state)
  {
    case GAME_STATE_MENU:
      update_menu(game);
      break;
    case GAME_STATE_PLAYING:
      break;
    case GAME_STATE_PAUSED:
      update_pause_menu(game);
      break;
    case GAME_STATE_SETTINGS:
      update_settings(game);
      break;
  }
}

void draw_current_state(Game *game)
{
  switch (game->state)
  {
    case GAME_STATE_MENU:
      draw_menu(game);
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

    case GAME_STATE_SETTINGS:
      // draw_settings(game);
      break;
  }
}

void unload_game(Game *game)
{
  unload_assets(&game->assets);
  unload_music(game);

  TraceLog(LOG_INFO, "Game shutdown complete");
}
