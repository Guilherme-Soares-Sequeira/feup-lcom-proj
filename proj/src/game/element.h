#ifndef INTERACTIVE_ELEMENT_H
#define INTERACTIVE_ELEMENT_H

#include <lcom/lcf.h>

#include <stdbool.h>

#include "cursor.h"

#include "../utils/position.h"


typedef struct {
  position top_pos;
  
  uint16_t h_len;
  uint16_t v_len;
  
  int8_t event_priority; 

  void (*draw_element)(position topleft_pos);

  void (*mouse_event_handler)(position top_pos, uint16_t h_len, uint16_t v_len);
} interactive_element;

bool (is_hovered)(interactive_element elem);

#endif
