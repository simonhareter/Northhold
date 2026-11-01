#ifndef MENU_H
#define MENU_H

#include "button.h"
#include <raylib.h>
#include <stdbool.h>

typedef struct Game Game;

typedef enum
{
  MENU_ITEM_PLAY,
  MENU_ITEM_SETTINGS,
  MENU_ITEM_EXIT,
  MENU_ITEM_COUNT
} MenuItem;

typedef struct
{
  Button options[MENU_ITEM_COUNT];
  int option_count;
} Menu;

void init_menu(Game *game);
void update_menu(Game *game);
void draw_menu(Game *game);
#endif
