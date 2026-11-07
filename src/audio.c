#include "audio.h"
#include "game.h"
#include <raylib.h>

void load_menu_music(Game *game)
{
  game->music.menu_music = LoadMusicStream("../assets/music/menu.mp3");
  game->music.menu_music.looping = true;
}

void load_playing_music(Game *game)
{
  game->music.playing1_music = LoadMusicStream("../assets/music/playing1.mp3");
  game->music.playing1_music.looping = true;
}

void update_menu_music(Game *game)
{
  UpdateMusicStream(game->music.menu_music);
}

void update_playing_music(Game *game)
{
  UpdateMusicStream(game->music.playing1_music);
}

void unload_music(Game *game)
{
  UnloadMusicStream(game->music.menu_music);
  UnloadMusicStream(game->music.playing1_music);
  CloseAudioDevice();
  TraceLog(LOG_INFO, "Unloaded audio device successfully");
}
