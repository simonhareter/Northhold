#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <stdbool.h>

#define BUTTON_COLOR               (Color){93, 0, 1, 255}
#define BUTTON_COLOR_HOVERED       (Color){113, 0, 1, 255}
#define BUTTON_TITLE_COLOR         (Color){21, 19, 24, 255}
#define BUTTON_TITLE_COLOR_HOVERED (Color){36, 34, 39, 255}
#define BUTTON_TEXT_COLOR          (Color){230, 224, 216, 255}
#define BUTTON_TITLE_TEXT_COLOR    (Color){214, 179, 59, 255}
#define BUTTON_OUTLINE_COLOR       (Color){26, 24, 29, 255}
#define BUTTON_ROUNDNESS           0.4
#define MENU_ROUNDNESS             0.04
#define BUTTON_SEGMENTS            100
#define BUTTON_OUTLINE_THICKNESS   4
#define BOX_OPACITY                0.8f
#define TEXT_SPACING               (FONT_SIZE * 0.05f)
#define H_ALIGN                    0.5f
#define V_ALIGN                    0.5f

typedef struct
{
  Rectangle outline;
  Rectangle rec;
  const char *text;
  bool is_hovered;
  Color outline_color;
  Color rec_color;
  Color hovered_color;
  float roundness;
} Button;

#endif
