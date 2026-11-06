#include "slider.h"
#include "button.h"
#include "config.h"
#include "settings.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

void init_slider(Settings *settings)
{
  float padding = 50;
  float gap = 50;

  float box_x = settings->ui_elements[BOX].rec.x;
  float box_y = settings->ui_elements[BOX].rec.y;
  float box_width = settings->ui_elements[0].rec.width;

  float rec_height = settings->ui_elements[TITLE].rec.height;

  float max_text_width = 0.0f;

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    Vector2 size = MeasureTextEx(settings->font, settings->options[i].name, SETTINGS_FONT_SIZE, TEXT_SPACING);

    if (size.x > max_text_width)
    {
      max_text_width = size.x;
    }
  }

  const char *value_example = "100";
  Vector2 value_size = MeasureTextEx(settings->font, value_example, SETTINGS_FONT_SIZE, TEXT_SPACING);

  float slider_width = box_width - max_text_width - padding * 2 - gap * 2 - value_size.x;

  float line_x = box_x + padding + max_text_width + gap;

  float line_height = 1;

  float knob_width = 15, knob_height = 25;

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    Setting *option = &settings->options[i];

    float option_y = box_y + padding + rec_height * i;
    Vector2 text_size = MeasureTextEx(settings->font, option->name, SETTINGS_FONT_SIZE, TEXT_SPACING);
    float center_y = option_y + text_size.y / 2.0f;

    float knob_percentage = option->value / 100.0f;
    float knob_x = line_x + knob_percentage * (slider_width - knob_width);

    Rectangle line = {line_x, center_y - line_height / 2, slider_width, line_height};
    Rectangle knob = {knob_x, center_y - knob_height / 2, knob_width, knob_height};

    option->slider = (Slider){line, knob, false};
  }
}

void update_slider(Settings *settings)
{
  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    Setting *option = &settings->options[i];
    Slider *slider = &option->slider;

    Vector2 mouse_pos = GetMousePosition();

    if (CheckCollisionPointRec(mouse_pos, slider->knob) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      slider->is_dragging = true;
    }

    if (slider->is_dragging && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
      int mouse_x = GetMouseX();

      slider->knob.x = mouse_x - slider->knob.width / 2;

      float min_x = slider->line.x;
      float max_x = slider->line.x + slider->line.width - slider->knob.width;

      slider->knob.x = Clamp(slider->knob.x, min_x, max_x);

      // update option value
      float travel_distance = slider->line.width - slider->knob.width;
      option->value = (int)roundf((slider->knob.x - slider->line.x) / travel_distance * 100);

      slider->knob.x = slider->line.x + (option->value / 100.0f) * travel_distance;
    }

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
      slider->is_dragging = false;
    }
  }
}

void draw_slider(Settings *settings)
{

  for (int i = 0; i < SETTINGS_COUNT; i++)
  {
    Setting option = settings->options[i];
    DrawRectangleRec(option.slider.line, BUTTON_TITLE_COLOR);
    DrawRectangleRec(option.slider.knob, BUTTON_COLOR);
  }
}
