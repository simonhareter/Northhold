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
  PAUSE_MENU_COUNT,
} PauseMenuItem;

typedef enum
{
  PAUSE_MENU_BOX,
  PAUSE_MENU_TITLE,
  PAUSE_MENU_UI_ELEMENTS_COUNT,
} PauseMenuUiElements;

typedef struct
{
  Button ui_elements[PAUSE_MENU_UI_ELEMENTS_COUNT];
  Button buttons[PAUSE_MENU_COUNT];
  Font pause_menu_font;
} PauseMenu;

void update_pause_menu(Game *game);
void init_pause_menu(Game *game);
void draw_pause_menu(Game *game);

#endif
