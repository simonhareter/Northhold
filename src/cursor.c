#include "cursor.h"
#include "button.h"
#include <raylib.h>
#include <stddef.h>

void update_cursor(bool is_hovering_interactive_element)
{
  if (is_hovering_interactive_element)
  {
    SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
  }
  else
  {
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
  }
}

bool is_mouse_over_button(Rectangle rec)
{
  Vector2 mouse_pos = {GetMouseX(), GetMouseY()};
  return CheckCollisionPointRec(mouse_pos, rec);
}

bool is_mouse_over_any_button(Button *options, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (is_mouse_over_button(options[i].rec))
    {
      options[i].is_hovered = true;
      return true;
    }
    else
    {
      options[i].is_hovered = false;
    }
  }
  return false;
}

int which_button_pressed(Button *options, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (is_mouse_over_button(options[i].rec) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
      return i;
    }
  }
  return -1;
}
