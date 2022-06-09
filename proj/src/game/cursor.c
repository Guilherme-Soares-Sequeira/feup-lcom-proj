#include <lcom/lcf.h>
#include <lcom/video_gr.h>

#include "../xpm/cursor.xpm"
#include "../xpm/bucket_cursor.xpm"
#include "cursor.h"

/* xpm images */

static xpm_image_t cursor_default_xpm; /**< @brief default cursor xpm */
static xpm_image_t cursor_bucket_xpm;  /**< @brief bucket cursor xpm */


/* cursor position */

static position cursor_pos = {0, 0}; /**< @brief cursor_position of the cursor */

static cursor_state_style_t cursor_style; /**< @brief style of the cursor */

static uint8_t cursor_color;
static uint8_t cursor_thickness;

static bool cursor_lb; /**< @brief indicates whether the mouse left button was already pressed or not */


void (cursor_load)() {
  cursor_default_xpm = vg_load_xpm(xpm_cursor_arrow);
  cursor_bucket_xpm  = vg_load_xpm(xpm_cursor_bucket);

  cursor_pos.x = H_RES/2;
  cursor_pos.y = V_RES/2;

  cursor_color = COLOR_BLACK;
  cursor_thickness = MIN_THICKNESS;
  
  cursor_lb = false;
}

xpm_image_t (cursor_get_xpm)() {
  /* in the future this needs to be changed */
  switch (cursor_style) {
    case CURSOR_DSTATE_CIRCLE: return cursor_default_xpm;
    case CURSOR_DSTATE_SQUARE: return cursor_default_xpm;
    case CURSOR_DSTATE_ARROW:  return cursor_default_xpm;
    case CURSOR_DSTATE_LINE:   return cursor_default_xpm;
    case CURSOR_DSTATE_BUCKET: return cursor_bucket_xpm;
    default: return cursor_default_xpm;
  }
}

void (cursor_move)(int16_t delta_x, int16_t delta_y) {
  cursor_pos.x = MIN(MAX(0, cursor_pos.x + delta_x), H_RES - cursor_get_xpm().width);
  cursor_pos.y = MIN(MAX(0, cursor_pos.y - delta_y), V_RES - cursor_get_xpm().height);
}

void (cursor_draw)() {
  vg_draw_xpm(cursor_get_xpm(), cursor_pos.x, cursor_pos.y);
}

void (cursor_clear)() {
  free(cursor_get_xpm().bytes);
}

void (cursor_set_style)(cursor_state_style_t style) {
  cursor_style = style;
}

cursor_state_style_t (cursor_get_style)() {
  return cursor_style;
}

void (cursor_set_thickness)(uint8_t thickness) {
  cursor_thickness = thickness;
}

uint8_t (cursor_get_thickness)() {
  return cursor_thickness;
}

position (cursor_get_pos)() {
  return cursor_pos;
}

bool (cursor_lb_pressed)() {
  return cursor_lb;
}

void (cursor_set_lb)(bool lb) {
  cursor_lb = lb;
}

uint8_t (cursor_get_color)() {
  return cursor_color;
}

void (cursor_increase_thickness)(uint8_t _) {
  cursor_thickness = cursor_thickness + 1 > MAX_THICKNESS ? MAX_THICKNESS : cursor_thickness + 1;
}

void (cursor_decrease_thickness)(uint8_t _) {
  cursor_thickness = cursor_thickness - 1 < MIN_THICKNESS ? MIN_THICKNESS : cursor_thickness - 1;
}

void (cursor_set_color)(uint8_t color) {
  cursor_color = color;
}

void (cursor_set_color_black)() {
  cursor_color = COLOR_BLACK;
}

void (cursor_set_color_blue)() {
  cursor_color = COLOR_BLUE;
}

void (cursor_set_color_green)() {
  cursor_color = COLOR_GREEN;
}

void (cursor_set_color_red)() {
  cursor_color = COLOR_RED;
}

void (cursor_set_color_brown)() {
  cursor_color = COLOR_BROWN;
}

void (cursor_set_color_yellow)() {
  cursor_color = COLOR_YELLOW;
}
