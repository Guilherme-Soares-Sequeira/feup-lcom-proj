#ifndef INTERACTIVE_ELEMENT_H
#define INTERACTIVE_ELEMENT_H

#include <lcom/lcf.h>

#include <stdbool.h>

#include "cursor.h"
#include "canvas.h"
#include "../utils/position.h"
#include "draw_buttons.h"

#define COLOR_BUTTON_PRIORITY 3
#define STYLE_BUTTON_PRIORITY 3

typedef struct {
  position top_pos;
  
  uint16_t h_len;
  uint16_t v_len;
  
  uint8_t color;

  int8_t event_priority; 

  void (*mouse_event_handler)(uint8_t color);
} interactive_element;

xpm_image_t (get_button_plus)();

void (load_ie_drawing)();

bool (is_hovered)(interactive_element elem);

uint8_t (get_number_of_drawing_ies)();

interactive_element* (get_drawing_ies)();

#endif
