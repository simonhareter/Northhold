#ifndef SETTINGS_H
#define SETTINGS_H

#include "button.h"
#include <raylib.h>

typedef struct Game Game;

typedef enum
{
  SETTINGS_MUSIC_VOLUME,
  SETTINGS_COUNT
} SettingsItem;

typedef struct
{
  Rectangle box;
  int volume;
  Button options[SETTINGS_COUNT];
} Settings;

void init_settings(Game *game);
void update_settings(Game *game);
void draw_settings(Game *game);

#endif
