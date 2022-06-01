#include <lcom/lcf.h>
#include <lcom/video_gr.h>

#include "../xpm/cursor.xpm"
#include "../xpm/bucket_cursor.xpm"
#include "cursor.h"


static xpm_image_t cursor_default_xpm;
static xpm_image_t cursor_bucket_xpm;


static position pos = {0, 0};

static cursor_state_t cursor_state;

static cursor_thickness_t cursor_thickness;

static bool lb;

void (cursor_load)() {
  cursor_default_xpm = vg_load_xpm(xpm_cursor_arrow);
  cursor_bucket_xpm = vg_load_xpm(xpm_cursor_bucket);
  pos.x = H_RES/2;
  pos.y = V_RES/2;
  lb = false;
}

void (cursor_move)(int16_t delta_x, int16_t delta_y) {
  pos.x = MIN(MAX(0, pos.x + delta_x), H_RES - cursor_xpm.width);
  pos.y = MIN(MAX(0, pos.y - delta_y), V_RES - cursor_xpm.height);
}

void (cursor_set_lb)(bool new_lb) {
  lb = new_lb;
}

void (cursor_draw)() {
  vg_draw_xpm(cursor_xpm, pos.x, pos.y);
}

void (cursor_clear)() {
  free(cursor_xpm.bytes);
}

void (cursor_set_state)(cursor_state_t state) {
  cursor_state = state;
}

cursor_state_t (cursor_get_state)() {
  return cursor_state;
}

void (cursor_set_thickness)(cursor_thickness_t thickness) {
  cursor_thickness = thickness;
}

cursor_thickness_t (cursor_get_thickness)() {
  return cursor_thickness;
}

position (cursor_get_pos)() {
  return pos;
}

bool (cursor_lb_pressed)() {
  return lb;
}
