#include "world.h"
#include <stdio.h>

void load_world(World *world)
{
    FILE *fptr;

    fptr = fopen("../assets/maps/map1.txt", "r");

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
