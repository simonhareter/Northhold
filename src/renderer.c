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
  for (int world_row = 0; world_row < WORLD_HEIGHT; world_row++)
  {
    for (int world_col = 0; world_col < WORLD_WIDTH; world_col++)
    {
      int tile_set_id = world->tiles[world_row][world_col].tile_set_id;
      int tile_id = world->tiles[world_row][world_col].tile_id;

      Texture2D texture = tile_assets->tile_sets[tile_set_id];

      int tiles_per_tile_set_row = 4;
      int row = tile_id / tiles_per_tile_set_row;
      int column = tile_id - (tiles_per_tile_set_row * row);

      float rec_x = (float)(TILE_SIZE * column);
      float rec_y = (float)(TILE_SIZE * row);

      Rectangle tile_rec = {rec_x, rec_y, TILE_SIZE, TILE_SIZE};
      Vector2 pos = {TILE_SIZE * world_col, TILE_SIZE * world_row};

      draw_tile(texture, tile_rec, pos, WHITE);
    }
  }
}

void draw_tile(Texture2D texture, Rectangle rec, Vector2 pos, Color tint)
{
  DrawTextureRec(texture, rec, pos, tint);
}
