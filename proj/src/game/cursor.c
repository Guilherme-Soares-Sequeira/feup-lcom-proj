#include <lcom/lcf.h>
#include <lcom/video_gr.h>

#include "../xpm/cursor.xpm"
#include "cursor.h"


static xpm_image_t cursor_xpm;

static position pos;

static bool lb;


void (cursor_load)() {
  cursor_xpm = vg_load_xpm(xpm_cursor_arrow);
  pos.x = 800/2;
  pos.y = 600/2;
  lb = false;
}

void (cursor_move)(int16_t delta_x, int16_t delta_y) {
  pos.x = MIN(MAX(0, pos.x + delta_x), 800 - cursor_xpm.width);
  pos.y = MIN(MAX(0, pos.y - delta_y), 600 - cursor_xpm.height);
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

position (cursor_get_pos)() {
  return pos;
}

bool (cursor_lb_pressed)() {
  return lb;
}
