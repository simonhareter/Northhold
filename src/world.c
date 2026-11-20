#include "world.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

// loads a predetermined map.txt
void load_world(World *world)
{
    FILE *fptr;

    fptr = fopen("assets/maps/map1.txt", "r");

    if (fptr == NULL)
    {
        perror("Failed to open map");
        return;
    }

    for (int i = 0; i < WORLD_HEIGHT; i++)
    {
        for (int j = 0; j < WORLD_WIDTH; j++)
        {
            int tile_set_id;
            int tile_id;

            if (fscanf(fptr, "%d,%d", &tile_set_id, &tile_id) == 2)
            {
                world->tiles[i][j] = (MapTile){
                    .tile_set_id = tile_set_id,
                    .tile_id = tile_id,
                    .walkable = false,
                };
            }
            else
            {
                fprintf(stderr, "Failed to read tile at [%d][%d]\n", i, j);
                fclose(fptr);
                return;
            }
        }
    }
    fclose(fptr);
}

void generate_world(World *world)
{
    // for now only use one tile_set and every tile is walkable
    int tile_set_id = GRASS_ROAD_TILE_SET;
    bool walkable = true;

    compute_tiles_adjacency_array(world);
    select_first_map_tile(world, tile_set_id, walkable);
    wave_function_collapse(world);
}

void compute_tiles_adjacency_array(World *world)
{
    const Tile tiles[TILE_SET_COUNT * TILES_PER_TILE_SET] = {
        {{GRASS, GRASS, GRASS, ROAD}},  {{GRASS, ROAD, ROAD, GRASS}},   {{ROAD, GRASS, ROAD, ROAD}},
        {{GRASS, GRASS, ROAD, ROAD}},   {{ROAD, GRASS, ROAD, GRASS}},   {{GRASS, ROAD, ROAD, ROAD}},
        {{ROAD, ROAD, ROAD, ROAD}},     {{ROAD, ROAD, GRASS, ROAD}},    {{GRASS, ROAD, GRASS, GRASS}},
        {{ROAD, ROAD, GRASS, GRASS}},   {{ROAD, ROAD, ROAD, GRASS}},    {{ROAD, GRASS, GRASS, ROAD}},
        {{GRASS, GRASS, GRASS, GRASS}}, {{GRASS, GRASS, ROAD, GRASS}},  {{GRASS, ROAD, GRASS, ROAD}},
        {{ROAD, GRASS, GRASS, GRASS}},  {{GRASS, GRASS, GRASS, WATER}}, {{GRASS, WATER, WATER, GRASS}},
        {{WATER, GRASS, WATER, WATER}}, {{GRASS, GRASS, WATER, WATER}}, {{WATER, GRASS, WATER, GRASS}},
        {{GRASS, WATER, WATER, WATER}}, {{WATER, WATER, WATER, WATER}}, {{WATER, WATER, GRASS, WATER}},
        {{GRASS, WATER, GRASS, GRASS}}, {{WATER, WATER, GRASS, GRASS}}, {{WATER, WATER, WATER, GRASS}},
        {{WATER, GRASS, GRASS, WATER}}, {{GRASS, GRASS, GRASS, GRASS}}, {{GRASS, GRASS, WATER, GRASS}},
        {{GRASS, WATER, GRASS, WATER}}, {{WATER, GRASS, GRASS, GRASS}},
    };

    // Example: tile_id = 0, looking for a tile north of tile_id 0 that fits.
    // tile 0 is grass at corners nw and ne -> so the tile to the north needs grass at sw and se!
    const int corner_relationships[CARDINAL_DIRECTION_COUNT][CORNERS_COUNT] = {
        [NORTH] = {NW, NE, SW, SE},
        [EAST] = {NE, SE, NW, SW},
        [SOUTH] = {SE, SW, NE, NW},
        [WEST] = {SW, NW, SE, NE},
    };

    for (int tile_id = 0; tile_id < TILE_COUNT; tile_id++)
    {
        for (int dir = 0; dir < CARDINAL_DIRECTION_COUNT; dir++)
        {
            for (int comparison_tile_id = 0; comparison_tile_id < TILE_COUNT; comparison_tile_id++)
            {
                const int *corner_rel = corner_relationships[dir];

                world->tiles_adjacency_array[tile_id][dir][comparison_tile_id] =
                    (bool)(tiles[tile_id].corners[corner_rel[0]] == tiles[comparison_tile_id].corners[corner_rel[2]] &&
                           tiles[tile_id].corners[corner_rel[1]] == tiles[comparison_tile_id].corners[corner_rel[3]]);
            }
        }
    }
}

void wave_function_collapse(World *world)
{
    // 1: Randomly choose a tile of the map and randomly select one of the 16 possible tile versions
    // 2: Now the tiles neighbours lose entropy (since only a certain amount of tiles fit to a specific side of the
    // first tile) Pick the direction with the lowest entropy.
    // If for instance the tile north of the first tile has 3 options, pick one at random. Once the tile
    // collapsed to a specific tile you know collapse that tile. rinse and repeat.
    // 3: With the dual grid 4x4 tileset, each tile has a predetermined amount of possible tile neighbors for all of its
    // four sides. Check the tileset.png in assets to see.
}

void propagate_constraints(World *world)
{
}

void select_first_map_tile(World *world, int tile_set_it, bool walkable)
{
    int first_tile_id = get_random_tile_id();
    Vector2 first_tile_pos = get_random_tile_pos();

    world->tiles[(int)first_tile_pos.y][(int)first_tile_pos.x] = (MapTile){
        .tile_set_id = tile_set_it,
        .tile_id = first_tile_id,
        .walkable = walkable,
        .collapsed = true,
    };

    propagate_constraints(world);
}

Vector2 get_random_tile_pos()
{
    return (Vector2){(float)GetRandomValue(0, WORLD_WIDTH - 1), (float)GetRandomValue(0, WORLD_HEIGHT - 1)};
}

int get_random_tile_id()
{
    return GetRandomValue(0, TILES_PER_TILE_SET - 1);
}