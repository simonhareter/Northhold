#include "world.h"
#include <stdio.h>

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
    const
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
    //
}
