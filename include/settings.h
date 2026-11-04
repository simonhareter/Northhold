#ifndef SETTINGS_H
#define SETTINGS_H

#include "button.h"
#include <raylib.h>

typedef struct Game Game;

typedef enum
{
  SETTINGS_MUSIC_VOLUME,
  SETTINGS_TEST1,
  SETTINGS_TEST2,
  SETTINGS_TEST3,
  SETTINGS_COUNT
} SettingsItem;

typedef enum
{
  BOX,
  TITLE,
  CANCEL,
  SAVE,
  SETTINGS_UI_ELEMENTS_COUNT
} SettingsUiElements;

typedef struct
{
  const char *name;
  int value;
} Setting;

typedef struct
{
  Button ui_elements[SETTINGS_UI_ELEMENTS_COUNT];
  int volume;
  Setting options[SETTINGS_COUNT];
  Font font;
} Settings;

void init_settings(Game *game);
void update_settings(Game *game);
void draw_settings(Game *game);

#endif
