#ifndef SLIDER_H
#define SLIDER_H

#include <raylib.h>

typedef struct Settings Settings;

typedef struct
{
  Rectangle line;
  Rectangle knob;
  bool is_dragging;
} Slider;

void init_slider(Settings *settings);
void update_slider(Settings *settings);
void draw_slider(Settings *settings);

#endif
