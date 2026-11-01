#ifndef CURSOR_H
#define CURSOR_H

#include "button.h"
#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>

void update_cursor(bool is_hovering_interactive_element);
bool is_mouse_over_button(Rectangle rec);
bool is_mouse_over_any_button(Button *options, size_t size);
int which_button_pressed(Button *options, size_t size);
#endif
