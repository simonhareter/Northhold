#ifndef AUDIO_H
#define AUDIO_H

#include <raylib.h>

typedef struct Game Game;

typedef struct
{
  Music menu_music;
  Music playing1_music;
} GameMusic;

void load_menu_music(Game *game);
void load_playing_music(Game *game);
void update_menu_music(Game *game);
void update_playing_music(Game *game);
void unload_music(Game *game);
void set_music_volume(GameMusic *music, int volume);
#endif
