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

  for(int i = 0; i < WORLD_HEIGHT; i++)
  {
    for(int j = 0; j < WORLD_WIDTH; j++)
    {
      int number;
      if(fscanf(fptr, "%d", &number) == 1)
      {
        int tile_set_id = (number >= 1 && number <= 16) ? 0 : 1;
        int tile_id = (tile_set_id == 0) ? number - 1 : number - 17;

        world->tiles[i][j] = (MapTile){tile_set_id, tile_id, false};

        if((j >= 0 && j <= 7) && i <= 3)
        {
          printf("%d \n", tile_set_id);
        }
      }
    }
  }
  fclose(fptr);
}
