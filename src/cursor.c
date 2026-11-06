#include "cursor.h"
#include "button.h"
#include "pause_menu.h"
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

bool is_mouse_over_slider_knob(Rectangle knob)
{
  Vector2 mouse_pos = {GetMouseX(), GetMouseY()};
  return CheckCollisionPointRec(mouse_pos, knob);
}

bool is_hovering_menu(Game *game)
{
  Button *options = game->menu.options;
  return is_mouse_over_any_button(options, MENU_ITEM_COUNT);
}

bool is_hovering_pause_menu(Game *game)
{
  Button *options = game->pause_menu.options;
  return is_mouse_over_any_button(options, PAUSE_MENU_COUNT);
}

bool is_hovering_settings(Game *game)
{
  // check if any knob is hovered
  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    Setting option = game->settings.options[i];

    if (is_mouse_over_slider_knob(option.slider.knob))
    {
      return true;
    }
  }

  return is_mouse_over_any_button(game->settings.buttons, SETTINGS_BUTTON_COUNT);
}
