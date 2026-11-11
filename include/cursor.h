#ifndef CURSOR_H
#define CURSOR_H

#include "button.h"
#include "game.h"
#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>

void update_cursor(bool is_hovering_interactive_element);
bool is_mouse_over_button(Rectangle rec);
bool is_mouse_over_any_button(Button *options, int size);
int which_button_pressed(Button *options, int size);
bool is_mouse_over_slider_knob(Rectangle knob);
bool is_hovering_settings(Game *game);
bool is_hovering_menu(Game *game);
bool is_hovering_pause_menu(Game *game);
#endif
