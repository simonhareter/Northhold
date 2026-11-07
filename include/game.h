#ifndef GAME_H
#define GAME_H

#include "assets.h"
#include "audio.h"
#include "menu.h"
#include "pause_menu.h"
#include "settings.h"
#include "world.h"
#include <raylib.h>
#include <stdbool.h>

typedef enum GameState
{
  GAME_STATE_MENU,
  GAME_STATE_PLAYING,
  GAME_STATE_PAUSED,
} GameState;

typedef enum OverlayState
{
  OVERLAY_STATE_NONE,
  OVERLAY_STATE_SETTINGS,
} OverlayState;

typedef struct Game
{
  Font font;
  Menu menu;
  Settings settings;
  PauseMenu pause_menu;
  GameState state;
  OverlayState overlay_state;
  World world;
  Assets assets;
  Camera2D camera;
  GameMusic music;
  bool should_exit;
} Game;

void init_game(Game *game);
void update_game(Game *game);
void draw_current_state(Game *game);
void unload_game(Game *game);

#endif
