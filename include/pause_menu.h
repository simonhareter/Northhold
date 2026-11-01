#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "button.h"
#include <raylib.h>

typedef struct Game Game;

typedef enum
{
  PAUSE_MENU_RESUME,
  PAUSE_MENU_SAVE,
  PAUSE_MENU_SETTINGS,
  PAUSE_MENU_EXIT,
  PAUSE_MENU_COUNT
} PauseMenuItem;

typedef struct
{
  Rectangle menu_box;
  Rectangle title_box;
  const char *pause_menu_title;
  Button options[PAUSE_MENU_COUNT];
} PauseMenu;

void update_pause_menu(Game *game);
void init_pause_menu(Game *game);
void draw_pause_menu(Game *game);

#endif
