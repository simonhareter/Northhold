#include "input.h"
#include "camera.h"
#include "game.h"
#include "settings.h"
#include <raylib.h>

void handle_input(Game *game)
{
    Camera2D *camera = &game->camera;

    // INGAME MENU
    if (IsKeyPressed(KEY_ESCAPE))
    {
        if (game->overlay_state == OVERLAY_STATE_SETTINGS)
        {
            cancel_settings(game);
            game->overlay_state = OVERLAY_STATE_NONE;
        }
        else if (game->state == GAME_STATE_PLAYING)
        {
            game->state = GAME_STATE_PAUSED;
        }
        else if (game->state == GAME_STATE_PAUSED)
        {
            game->state = GAME_STATE_PLAYING;
        }
    }

    // CAMERA MOVEMENT
    if (game->state == GAME_STATE_PLAYING)
    {
        if (IsKeyDown(KEY_RIGHT))
        {
            move_camera(camera, KEY_RIGHT);
        }

        if (IsKeyDown(KEY_LEFT))
        {
            move_camera(camera, KEY_LEFT);
        }

        if (IsKeyDown(KEY_UP))
        {
            move_camera(camera, KEY_UP);
        }

        if (IsKeyDown(KEY_DOWN))
        {
            move_camera(camera, KEY_DOWN);
        }
    }
}
