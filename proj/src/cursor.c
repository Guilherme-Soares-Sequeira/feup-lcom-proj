#include <lcom/lcf.h>
#include "cursor.h"
#include <lcom/video_gr.h>
#include "devices/video/video_gr.h"

#include "xpm/cursor.xpm"

static xpm_image_t cursor_xpm;

static int16_t cursor_x;
static int16_t cursor_y;

static bool lb;


void (cursor_load)() {
  cursor_xpm = vg_load_xpm(xpm_cursor_arrow);
  cursor_x = 1024/2;
  cursor_y = 768/2;
  lb = false;
}

void (cursor_move)(int16_t delta_x, int16_t delta_y) {
  cursor_x = MIN(MAX(0, cursor_x + delta_x), 1024 - cursor_xpm.width);
  cursor_y = MIN(MAX(0, cursor_y - delta_y), 768 - cursor_xpm.height);
}

void (cursor_set_lb)(bool new_lb) {
  lb = new_lb;
}

void (cursor_draw)() {
  vg_draw_xpm(cursor_xpm, cursor_x, cursor_y);
}

void (cursor_clear)() {
  free(cursor_xpm.bytes);
}

bool (cursor_lb_pressed)() {
  return lb;
}
