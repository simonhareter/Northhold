#ifndef GAME_H
#define GAME_H

#include "assets.h"
#include "menu.h"
#include "pause_menu.h"
#include "world.h"
#include <raylib.h>
#include <stdbool.h>

typedef enum GameState
{
  GAME_STATE_MENU,
  GAME_STATE_PLAYING,
  GAME_STATE_PAUSED,
  GAME_STATE_SETTINGS
} GameState;

typedef struct Game
{
  Font font;
  Menu menu;
  PauseMenu pause_menu;
  GameState state;
  World world;
  Assets assets;
  Camera2D camera;
  Music menu_music;
  bool should_exit;
} Game;

void init_game(Game *game);
void update_game(Game *game);
void draw_current_state(Game *game);
void unload_game(Game *game);

#endif
