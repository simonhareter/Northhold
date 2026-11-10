#include "renderer.h"
#include "assets.h"
#include "game.h"
#include "world.h"

void draw_game(Game *game)
{
  draw_world(&game->world, &game->assets.tile_assets);
}

void draw_world(const World *world, const TileAssets *tile_assets)
{
  for (int y = 0; y < WORLD_HEIGHT; y++)
  {
    for (int x = 0; x < WORLD_WIDTH; x++)
    {
      int tile_set_id = world->tiles[y][x].tile_set_id;
      int tile_id = world->tiles[y][x].tile_id;

      Texture2D texture = tile_assets->tile_sets[tile_set_id];

      int tiles_per_tile_set_row = 4;
      int row = tile_id / tiles_per_tile_set_row;
      int column = tile_id - tiles_per_tile_set_row * row;

      int rec_x = TILE_SIZE * column;
      int rec_y = TILE_SIZE * row;

      Rectangle tile_rec = {rec_x, rec_y, TILE_SIZE, TILE_SIZE};
      Vector2 pos = {TILE_SIZE * x, TILE_SIZE * y};

      draw_tile(texture, tile_rec, pos, WHITE);
    }
  }
}

void draw_tile(Texture2D texture, Rectangle rec, Vector2 pos, Color tint)
{
  DrawTextureRec(texture, rec, pos, tint);
}
