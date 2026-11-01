#include "assets.h"
#include "world.h"
#include <raylib.h>

void load_assets(Assets *assets)
{
  load_tile_assets(&assets->tile_assets);
}

void load_tile_assets(TileAssets *tile_assets)
{
  tile_assets->terrain[TERRAIN_GRASS] = LoadTexture("../assets/tiles/grass.png");
  tile_assets->terrain[TERRAIN_WATER] = LoadTexture("../assets/tiles/water.png");
  tile_assets->terrain[TERRAIN_ROAD] = LoadTexture("../assets/tiles/road.png");
  tile_assets->terrain[TERRAIN_STONE] = LoadTexture("../assets/tiles/stone.png");
  tile_assets->terrain[TERRAIN_SAND] = LoadTexture("../assets/tiles/sand.png");
}

void unload_assets(Assets *assets)
{
  unload_tile_assets(&assets->tile_assets);
}

void unload_tile_assets(TileAssets *tile_assets)
{
  for (int i = 0; i < TERRAIN_COUNT; i++)
  {
    UnloadTexture(tile_assets->terrain[i]);
  }
  TraceLog(LOG_INFO, "Unloaded tile assets");
}
