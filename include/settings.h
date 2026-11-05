#ifndef SETTINGS_H
#define SETTINGS_H

#include "button.h"
#include "slider.h"
#include <raylib.h>

typedef struct Game Game;

typedef enum
{
  SETTINGS_MUSIC_VOLUME,
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
  int min_value;
  int max_value;
  Slider slider;
} Setting;

typedef struct Settings
{
  Button ui_elements[SETTINGS_UI_ELEMENTS_COUNT];
  Setting options[SETTINGS_COUNT];
  Font font;
} Settings;

void init_settings(Game *game);
void update_settings(Game *game);
void draw_settings(Game *game);
void draw_ui_elements(Game *game);
void draw_options(Game *game);


#endif
