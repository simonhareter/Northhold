#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>

typedef enum
{
  GRASS_ROAD_TILE_SET,
  GRASS_WATER_TILE_SET,
  TILE_SET_COUNT,
} TileSet;

typedef struct
{
  int tile_set_id;
  int tile_id;
  bool walkable;
} MapTile;

#define WORLD_WIDTH     16
#define WORLD_HEIGHT    16
#define TILE_SIZE       32
#define WORLD_WIDTH_PX  (WORLD_WIDTH * TILE_SIZE)
#define WORLD_HEIGHT_PX (WORLD_HEIGHT * TILE_SIZE)

typedef struct
{
  MapTile tiles[WORLD_HEIGHT][WORLD_WIDTH];
} World;

void load_world(World *world);
void generate_world(World *world);
#endif
