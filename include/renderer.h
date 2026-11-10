#ifndef RENDERER_H
#define RENDERER_H

#include "assets.h"
#include "game.h"
#include "world.h"
#include <raylib.h>

void draw_game(Game *game);
void draw_world(const World *world, const TileAssets *tile_assets);
void draw_tile(Texture2D texture, Rectangle rec, Vector2 pos, Color ting);

#endif
