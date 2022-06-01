#include <lcom/lcf.h>

#include "graphics.h"

int (buf_draw_pixel)(pixel_buffer const * const buf, position pos, uint8_t color) {
  if (pos.x >= H_RES || pos.y >= V_RES)
    return 0;
  
  int pixel_offset = pos.x + pos.y * H_RES;
  int byte_offset = pixel_offset * buf->bytes_per_pixel;

  uint8_t *pixel_start = (uint8_t *) buf->buffer_start + byte_offset;

  pixel_start[0] = color;

  return 0;
}

int(_buf_draw_line_low)(pixel_buffer const * const buf, uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, uint16_t dx, uint16_t dy, uint8_t color) {
  int yi = 1;

  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }

  int D = 2 * dy - dx;
  int y = from_y;

  for (int x = from_x; x <= to_x; x++) {
    if (buf_draw_pixel(buf, (position) {x, y}, color)) {
      fprintf(stderr, "There was an error drawing a pixel at %s!\n", __func__);
      return 1;
    }

    if (D > 0) {
      y += yi;
      D += 2 * (dy - dx);
    }
    else
      D += 2 * dy;
  }

  return OK;
}

int(_buf_draw_line_high)(pixel_buffer const * const buf, uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, uint16_t dx, uint16_t dy, uint8_t color) {
  int xi = 1;

  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }

  int D = 2 * dx - dy;
  int x = from_x;

  for (int y = from_y; y <= to_y; y++) {
    if (buf_draw_pixel(buf, (position) {x, y}, color)) {
      fprintf(stderr, "There was an error drawing a pixel at %s!\n", __func__);
      return 1;
    }

    if (D > 0) {
      x += xi;
      D += 2 * (dx - dy);
    }
    else
      D += 2 * dx;
  }

  return OK;
}

int (buf_draw_line)(pixel_buffer const * const buf, position from_pos, position to_pos, uint8_t color) {
  uint16_t dx = to_pos.x - from_pos.x;
  uint16_t dy = to_pos.y - from_pos.y;
  if (abs(dy) < abs(dx))
    if (from_pos.x > to_pos.x)
      return _buf_draw_line_low(buf, from_pos.x, from_pos.y, to_pos.x, to_pos.y, dx, dy, color);
    else
      return _buf_draw_line_low(buf, from_pos.x, from_pos.y, to_pos.x, to_pos.y, dx, dy, color);
  else if (from_pos.y > to_pos.y)
    return _buf_draw_line_high(buf, from_pos.x, from_pos.y, to_pos.x, to_pos.y, dx, dy, color);
  else
    return _buf_draw_line_high(buf, from_pos.x, from_pos.y, to_pos.x, to_pos.y, dx, dy, color);

}

int (buf_draw_rectangle)(pixel_buffer const * const buf, position pos, uint16_t width, uint16_t height, uint8_t color) {
  int i = (pos.x + pos.y * H_RES) * buf->bytes_per_pixel;
  int offset = H_RES * buf->bytes_per_pixel;
  
  width *= buf->bytes_per_pixel;

  for (int j = 0; j < height; ++j, i += offset)
    memset((uint8_t*)buf->buffer_start + i, color, width);
  
  return 0;
}

int (buf_draw_circle)(pixel_buffer const * const buf, position pos, uint16_t radius, uint8_t color) {
  uint16_t top_left_x = pos.x - radius;
  uint16_t top_left_y = pos.y - radius;
  uint32_t max_distance = radius * radius;
  uint32_t x32 = pos.x, y32 = pos.y;

  for (uint32_t i = top_left_x; i <= top_left_x + 2 * radius; i++) {
    for (uint32_t j = top_left_y; j <= top_left_y + 2 * radius; j++) {
      if ((x32 - i) * (x32 - i) + (y32 - j) * (y32 - j) <= max_distance) {
        if (buf_draw_pixel(buf, (position) {i, j}, color)) {
          fprintf(stderr, "There was an error drawing a pixel at %s!\n", __func__);
          return 1;
        }
      }
    }
  }

  return 0;
}
