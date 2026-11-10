#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"
#include "world.h"

typedef struct
{
  Texture2D tile_sets[TILE_SET_COUNT];
} TileAssets;

typedef struct
{
  TileAssets tile_assets;
} Assets;

void load_assets(Assets *assets);
void load_tile_assets(TileAssets *tile_assets);
void unload_assets(Assets *assets);
void unload_tile_assets(TileAssets *tile_assets);
#endif
