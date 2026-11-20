#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>
#include <stdbool.h>

typedef enum
{
  GRASS_ROAD_TILE_SET,
  GRASS_WATER_TILE_SET,
  TILE_SET_COUNT,
} TileSet;

typedef enum
{
  NORTH,
  EAST,
  SOUTH,
  WEST,
  CARDINAL_DIRECTION_COUNT,
} CardinalDirection;

typedef enum
{
  GRASS,
  ROAD,
  WATER,
  ADJACENCY_VALUES_COUNT,
} AdjacencyValue;

typedef enum
{
  NW,
  NE,
  SE,
  SW,
  CORNERS_COUNT
} Corner;

typedef struct
{
  int corners[CORNERS_COUNT];
} Tile;

typedef struct
{
  int tile_set_id;
  int tile_id;
  bool walkable;
  float entropy;
  bool collapsed;
} MapTile;

#define WORLD_WIDTH     16 // MapTiles
#define WORLD_HEIGHT    16 // MapTiles
#define TILE_SIZE       32 // Pixels
#define TILES_PER_TILE_SET 16
#define TILE_COUNT (TILES_PER_TILE_SET * TILE_SET_COUNT)
#define WORLD_WIDTH_PX  (WORLD_WIDTH * TILE_SIZE)
#define WORLD_HEIGHT_PX (WORLD_HEIGHT * TILE_SIZE)

typedef struct
{
  MapTile tiles[WORLD_HEIGHT][WORLD_WIDTH];
  bool tiles_adjacency_array[TILE_COUNT][CARDINAL_DIRECTION_COUNT][TILE_COUNT];
} World;

void load_world(World *world);
void generate_world(World *world);
void compute_tiles_adjacency_array(World *world);
void print_adjacency_array(World *world);
void wave_function_collapse(World *world);
void propagate_constraints(World *world);
void select_first_map_tile(World *world, int tile_set_it, bool walkable);
int get_random_tile_id();
Vector2 get_random_tile_pos();

#endif
