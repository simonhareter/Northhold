#include "audio.h"
#include "game.h"
#include <raylib.h>

void play_menu_music(Game *game)
{
  game->menu_music = LoadMusicStream("../assets/music/menu.mp3");
  game->menu_music.looping = true;
}

void update_menu_music(Game *game)
{
  UpdateMusicStream(game->menu_music);
}

void unload_music(Game *game)
{
  UnloadMusicStream(game->menu_music);
  CloseAudioDevice();
  TraceLog(LOG_INFO, "Unloaded audio device successfully");
}
