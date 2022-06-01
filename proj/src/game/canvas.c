#include <lcom/lcf.h>

#include "canvas.h"

static pixel_buffer canvas_buffer;

static uint32_t (canvas_get_buffer_size)() {
  return canvas_buffer.h_res * canvas_buffer.v_res * canvas_buffer.bytes_per_pixel;
}

void (canvas_load)() {
  canvas_buffer.h_res = H_RES;
  canvas_buffer.v_res = CANVAS_BOTTOM_VISIBLE_LIMIT;
  canvas_buffer.bytes_per_pixel = CANVAS_BYPP;
  canvas_buffer.buffer_start = malloc(canvas_get_buffer_size());
  canvas_clear();
}

void (canvas_draw)() {
  memcpy(vg_get_back_buffer(), canvas_buffer.buffer_start, canvas_get_buffer_size());
}

void (canvas_fill)(uint8_t color) {
  memset(canvas_buffer.buffer_start, color, canvas_get_buffer_size());
}

int (canvas_draw_pencil_circle)() {
  uint16_t thickness = 10;
  return buf_draw_circle(&canvas_buffer, cursor_get_pos(), thickness, 0x10);
}

void (canvas_clear)() {
  canvas_fill(COLOR_WHITE);
}

void (canvas_exit)() {
  free(canvas_buffer.buffer_start);
}


