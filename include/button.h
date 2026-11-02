#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <stdbool.h>

#define BUTTON_COLOR             (Color){93, 0, 1, 255}
#define BUTTON_COLOR_HOVERED     (Color){113, 0, 1, 255}
#define BUTTON_TITLE_COLOR       (Color){26, 24, 29, 255}
#define BUTTON_TEXT_COLOR        (Color){230, 224, 216, 255}
#define BUTTON_TITLE_TEXT_COLOR  (Color){214, 179, 59, 255}
#define BUTTON_OUTLINE_COLOR     (Color){26, 24, 29, 255}
#define BUTTON_ROUNDNESS         0.4
#define BUTTON_SEGMENTS          100
#define BUTTON_OUTLINE_THICKNESS 4

typedef struct
{
  Rectangle outline;
  Rectangle rec;
  const char *text;
  bool is_hovered;
} Button;

#endif
