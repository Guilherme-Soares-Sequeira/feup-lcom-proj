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

int(canvas_draw_line_low)(position from_pos, position to_pos, int16_t dx, int16_t dy) {
  int yi = 1;

  uint8_t thickness = cursor_get_thickness();
  cursor_state_style_t style = cursor_get_style();

  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }

  int D = 2 * dy - dx;
  int y = from_pos.y;

  for (int x = from_pos.x; x <= to_pos.x; x++) {
    //if ((x - from_pos.x) % thickness == 0) { //ADD ONLY IF PERFORMANCE IS NEEDED
      if (style == CURSOR_DSTATE_CIRCLE) {
        if (buf_draw_circle(&canvas_buffer, (position) {x, y}, thickness, cursor_get_color()))
          return 1;
      }
      else if ( style == CURSOR_DSTATE_SQUARE) {
        if (buf_draw_rectangle(&canvas_buffer, (position) { x - thickness/2, y - thickness/2}, thickness, thickness, cursor_get_color()))
          return 1;
      }
    //}
    if (D > 0) {
      y += yi;
      D += 2 * (dy - dx);
    }
    else
      D += 2 * dy;
  }

  return OK;
}

int(canvas_draw_line_high)(position from_pos, position to_pos, int16_t dx, int16_t dy) {
  int xi = 1;

  uint8_t thickness = cursor_get_thickness();
  cursor_state_style_t style = cursor_get_style();

  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }

  int D = 2 * dx - dy;
  int x = from_pos.x;

  for (int y = from_pos.y; y <= to_pos.y; y++) {
    //if ((y - from_pos.y) % thickness == 0) { //ADD ONLY IF PERFORMANCE IS NEEDED

      if (style == CURSOR_DSTATE_CIRCLE) {
        if (buf_draw_circle(&canvas_buffer, (position) {x, y}, thickness, cursor_get_color()))
          return 1;
      }
      else if (style == CURSOR_DSTATE_SQUARE) {
        if (buf_draw_rectangle(&canvas_buffer, (position) { x - thickness/2, y - thickness/2}, thickness, thickness, cursor_get_color()))
          return 1;
      }
    //}

    if (D > 0) {
      x += xi;
      D += 2 * (dx - dy);
    }
    else
      D += 2 * dx;
  }

  return OK;
}

int(canvas_draw_line)(position from_pos, position to_pos) {
  int16_t dx = to_pos.x - from_pos.x;
  int16_t dy = to_pos.y - from_pos.y;
  if (abs(dy) < abs(dx))
    if (from_pos.x > to_pos.x)
      return canvas_draw_line_low(to_pos, from_pos, -dx, -dy);
    else
      return canvas_draw_line_low(from_pos, to_pos, dx, dy);
  else if (from_pos.y > to_pos.y)
    return canvas_draw_line_high(to_pos, from_pos, -dx, -dy);
  else
    return canvas_draw_line_high(from_pos, to_pos, dx, dy);
}

/*
  This also works. It's known as the Bresenham's line algorithm
  More information here: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
*/

// int (canvas_draw_test)(position from_pos, position to_pos) {
//   int16_t x0 = from_pos.x, y0 = from_pos.y;
//   int16_t x1 = to_pos.x, y1 = to_pos.y;

//   int16_t dx = abs(x1 - x0);
//   int16_t sx = x0 < x1 ? 1 : -1;
//   int16_t dy = -abs(y1 - y0);
//   int16_t sy = y0 < y1 ? 1 : -1;
  
//   int32_t error = dx + dy;

//   while (true) {
//     if (buf_draw_circle(&canvas_buffer, (position) {x0, y0}, cursor_get_thickness(), cursor_get_color()) != OK)
//       return EXIT_FAILURE;

//     if (x0 == x1 && y0 == y1) 
//       break;

//     int32_t error2 = 2 * error;

//     if (error2 >= dy) {
//       if (x0 == x1) break;
//       error += dy;
//       x0 += sx;
//     }

//     if (error2 <= dx) {
//       if (y0 == y1) break;
//       error += dx;
//       y0 += sy;
//     }
//   }

//   return OK; 
// }

int (canvas_draw_pencil_circle)() {
  int ret = 0;
  
  uint8_t thickness = cursor_get_thickness();
  uint8_t color = cursor_get_color();
  
  mouse_packet_t mouse_packet = get_mouse_packet();
  position final_position = cursor_get_pos();
  position initial_position = (position) {final_position.x - mouse_packet.delta_x, final_position.y + mouse_packet.delta_y};  

  if (abs(mouse_packet.delta_x) + abs(mouse_packet.delta_y) >= 2*thickness) {
    ret = canvas_draw_line(initial_position, final_position) || ret;
  }
  else {
    ret = buf_draw_circle(&canvas_buffer, final_position, thickness, color) || ret;
    ret = buf_draw_circle(&canvas_buffer, initial_position, thickness, color) || ret;
  }

  return ret;
}

int (canvas_draw_pencil_square)() {
  int ret = 0;
  
  uint8_t thickness = cursor_get_thickness();
  uint8_t color = cursor_get_color();
  
  mouse_packet_t mouse_packet = get_mouse_packet();
  position final_position = cursor_get_pos();
  position initial_position = (position) {final_position.x - mouse_packet.delta_x, final_position.y + mouse_packet.delta_y};  

  if (abs(mouse_packet.delta_x) + abs(mouse_packet.delta_y) >= 2*thickness) {
    ret = canvas_draw_line(initial_position, final_position) || ret;
  }
  else {
    ret = buf_draw_rectangle(&canvas_buffer, (position) { final_position.x - thickness/2, final_position.y - thickness/2}, thickness, thickness, color) || ret;
    ret = buf_draw_rectangle(&canvas_buffer, (position) { initial_position.x - thickness/2, initial_position.y - thickness/2}, thickness, thickness, color) || ret;
  }

  return ret;

}

void (canvas_clear)() {
  canvas_fill(COLOR_WHITE);
}

void (canvas_exit)() {
  free(canvas_buffer.buffer_start);
}

pixel_buffer const * (get_canvas_buffer)() {
  return &canvas_buffer;
}

void (canvas_mouse_handler)(uint8_t _) {
  switch(cursor_get_style()) {
    case CURSOR_DSTATE_CIRCLE: canvas_draw_pencil_circle(); break;
    case CURSOR_DSTATE_SQUARE: canvas_draw_pencil_square(); break;
    case CURSOR_DSTATE_ARROW: break;
    case CURSOR_DSTATE_LINE: break;
    case CURSOR_DSTATE_BUCKET: break;
  }
}
