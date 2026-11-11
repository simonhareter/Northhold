#include "assets.h"
#include "world.h"
#include <raylib.h>

void load_assets(Assets *assets)
{
    load_tile_assets(&assets->tile_assets);
}

void load_tile_assets(TileAssets *tile_assets)
{
    tile_assets->tile_sets[GRASS_ROAD_TILE_SET] = LoadTexture("assets/tiles/tilesets/grass_road.png");
    tile_assets->tile_sets[GRASS_WATER_TILE_SET] = LoadTexture("assets/tiles/tilesets/grass_water.png");
}

void unload_assets(Assets *assets)
{
    unload_tile_assets(&assets->tile_assets);
}

void unload_tile_assets(TileAssets *tile_assets)
{
    for (int i = 0; i < TILE_SET_COUNT; i++)
    {
        UnloadTexture(tile_assets->tile_sets[i]);
    }
    TraceLog(LOG_INFO, "Unloaded tile assets successfully");
}
