#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>

typedef enum
{
  GRASS_ROAD_TILE_SET,
  GRASS_WATER_TILE_SET,
  TILE_SET_COUNT
} TileSet; 

typedef struct
{
  int tile_set_id;
  int tile_id;
  bool walkable;
} MapTile;

#define WORLD_WIDTH 128
#define WORLD_HEIGHT 128
#define TILE_SIZE 32

typedef struct
{
  MapTile tiles[WORLD_HEIGHT][WORLD_WIDTH];
} World;

void load_world(World *world);
void generate_world(World *world);
#endif
