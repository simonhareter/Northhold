#include "settings.h"
#include "button.h"
#include "config.h"
#include "game.h"
#include <raylib.h>

void init_settings(Game *game)
{
  float box_width = 400;
  float box_height = 450;
  Rectangle box = {SCREEN_WIDTH / 2.0f - box_width / 2.0f, SCREEN_HEIGHT / 2.0f - box_height / 2.0f, box_width,
                   box_height};

  game->settings.box = box;
}

void update_settings(Game *game)
{
}

void draw_settings(Game *game)
{
  DrawRectangleRec(game->settings.box, WHITE);
}
