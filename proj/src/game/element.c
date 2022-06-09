#include <lcom/lcf.h>

#include "element.h"

static interactive_element *drawing_ies;

static uint8_t number_of_drawing_ies;

void (load_ie_drawing)() {
  /* create elements */
  interactive_element black_color_button = {
    (position) {974, 70},
    40,
    40,
    COLOR_BLACK,
    3,
    cursor_set_color
  };

  interactive_element blue_color_button = {
    (position) {974, 120},
    40,
    40,
    COLOR_BLUE,
    3,
    cursor_set_color
  };

  interactive_element green_color_button = {
    (position) {974, 170},
    40,
    40,
    COLOR_GREEN,
    3,
    cursor_set_color
  };

  interactive_element red_color_button = {
    (position) {974, 220},
    40,
    40,
    COLOR_RED,
    3,
    cursor_set_color
  };
  
  interactive_element brown_color_button = {
    (position) {974, 270},
    40,
    40,
    COLOR_BROWN,
    3,
    cursor_set_color
  };

  interactive_element yellow_color_button = {
    (position) {974, 320},
    40,
    40,
    COLOR_YELLOW,
    3,
    cursor_set_color
  };

  interactive_element plus_button = {
    (position) {10, 70},
    40,
    40,
    COLOR_TRANSPARENT,
    3,
    cursor_increase_thickness
  };

  interactive_element minus_button = {
    (position) {10, 120},
    40,
    40,
    COLOR_TRANSPARENT,
    3,
    cursor_decrease_thickness
  };

  interactive_element clear_canvas_button = {
    (position) {10, 320},
    40,
    40,
    COLOR_WHITE,
    3,
    canvas_fill
  };

  interactive_element canvas = {
    (position) {CANVAS_TOP_VISIBLE_LIMIT, CANVAS_LEFT_VISIBLE_LIMIT},
    CANVAS_WIDTH,
    CANVAS_HEIGHT,
    COLOR_TRANSPARENT,
    1,
    canvas_mouse_handler
  };

  number_of_drawing_ies = 10;

  drawing_ies = (interactive_element*)malloc(number_of_drawing_ies * sizeof(interactive_element));

  memcpy(drawing_ies, (interactive_element[]){canvas, black_color_button, blue_color_button, green_color_button, red_color_button,
  brown_color_button, yellow_color_button, plus_button, minus_button, clear_canvas_button}, number_of_drawing_ies * sizeof(interactive_element));
  
}


bool (is_hovered)(interactive_element elem) {
  position mouse_position = cursor_get_pos();

  return (mouse_position.x >= elem.top_pos.x && 
          mouse_position.x < elem.top_pos.x + elem.h_len &&
          mouse_position.y >= elem.top_pos.y &&
          mouse_position.y < elem.top_pos.y + elem.v_len);
}

uint8_t (get_number_of_drawing_ies)() {
  return number_of_drawing_ies;
}

interactive_element* (get_drawing_ies)() {
  return drawing_ies;
}

