#include "config.h"
#include "game.h"
#include "input.h"
#include <raylib.h>

//------------------------------------------------------------------------------------
// Stronghold main entry point
//------------------------------------------------------------------------------------
int main(void)
{

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Northhold");
  SetExitKey(KEY_F8);
  SetTargetFPS(60);

  Game game;
  init_game(&game);

  while (!WindowShouldClose() && !game.should_exit)
  {
    handle_input(&game);
    update_game(&game);

    BeginDrawing();

    ClearBackground(BLACK);
    draw_current_state(&game);

    EndDrawing();
  }

  unload_game(&game);
  CloseWindow(); // Close window and OpenGL context

  return 0;
}
