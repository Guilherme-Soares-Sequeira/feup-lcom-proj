#include <lcom/lcf.h>

#include "../devices/video/graphics.h"
#include "draw_buttons.h"

/* button xpms */

static xpm_image_t button_plus, button_minus, button_clear_canvas;


xpm_image_t (get_button_plus)(){ return button_plus; }

void (load_button_xpms)() {
  button_plus = vg_load_xpm(xpm_button_plus);
  button_minus = vg_load_xpm(xpm_button_minus);
  button_clear_canvas = vg_load_xpm(xpm_button_clear_canvas);
}

void (draw_button_frame)(pixel_buffer const * const buf, position topleft_pos) {
  buf_draw_hline(buf, topleft_pos, BUTTON_FRAME_WIDTH, BUTTON_FRAME_COLOR);
  buf_draw_hline(buf, (position) {topleft_pos.x, topleft_pos.y + 1}, BUTTON_FRAME_WIDTH, BUTTON_FRAME_COLOR);
  buf_draw_hline(buf, (position) {topleft_pos.x, topleft_pos.y + BUTTON_FRAME_HEIGHT - 2}, BUTTON_FRAME_WIDTH, BUTTON_FRAME_COLOR);
  buf_draw_hline(buf, (position) {topleft_pos.x, topleft_pos.y + BUTTON_FRAME_HEIGHT - 1}, BUTTON_FRAME_WIDTH, BUTTON_FRAME_COLOR);

  buf_draw_vline(buf, (position) {topleft_pos.x, topleft_pos.y + 2}, BUTTON_FRAME_HEIGHT - 4, BUTTON_FRAME_COLOR);
  buf_draw_vline(buf, (position) {topleft_pos.x + 1, topleft_pos.y + 2}, BUTTON_FRAME_HEIGHT - 4, BUTTON_FRAME_COLOR);
  buf_draw_vline(buf, (position) {topleft_pos.x + BUTTON_FRAME_WIDTH - 2, topleft_pos.y + 2}, BUTTON_FRAME_HEIGHT - 4, BUTTON_FRAME_COLOR);
  buf_draw_vline(buf, (position) {topleft_pos.x + BUTTON_FRAME_WIDTH - 1, topleft_pos.y + 2}, BUTTON_FRAME_HEIGHT - 4, BUTTON_FRAME_COLOR);
}

void (draw_color_button)(pixel_buffer const * const buf, position topleft_pos, uint8_t color) {
  draw_button_frame(buf, topleft_pos);
  buf_draw_rectangle(buf, (position) {topleft_pos.x + 2, topleft_pos.y + 2}, BUTTON_FRAME_WIDTH - 4, BUTTON_FRAME_HEIGHT - 4, color);
}

void (draw_plus_button)(pixel_buffer const * const buf, position topleft_pos) {
  buf_draw_xpm(buf, button_plus, topleft_pos);
}

void (draw_minus_button)(pixel_buffer const * const buf, position topleft_pos) {
   buf_draw_xpm(buf, button_minus, topleft_pos);
}

void (draw_sel_line_button)(pixel_buffer const * const buf, position topleft_pos) {

}

void (draw_sel_square_button)(pixel_buffer const * const buf, position topleft_pos) {

}

void (draw_sel_circle_button)(pixel_buffer const * const buf, position topleft_pos) {

}

void (draw_sel_eraser_button)(pixel_buffer const * const buf, position topleft_pos) {
  
}

void (draw_clear_canvas_button)(pixel_buffer const * const buf, position topleft_pos) {
   buf_draw_xpm(buf, button_clear_canvas, topleft_pos);
}

void (buttons_draw)() {
  const pixel_buffer *const buf = get_back_buffer();
  const int color_button_x = CANVAS_RIGHT_VISIBLE_LIMIT + (CANVAS_MARGIN - BUTTON_FRAME_WIDTH)/2;
  const int other_buttons_x = (CANVAS_MARGIN - BUTTON_FRAME_WIDTH)/2;
  draw_color_button(buf, (position) {color_button_x, 70}, COLOR_BLACK); // y = CANVAS_TOP_VISIBLE_LIMIT + (CANVAS_MARGIN - BUTTON_FRAME_HEIGHT) / 2
  draw_color_button(buf, (position) {color_button_x, 120}, COLOR_BLUE); // y = previous_y() + (CANVAS_MARGIN - BUTTON_FRAME_HEIGHT) / 2
  draw_color_button(buf, (position) {color_button_x, 170}, COLOR_GREEN);
  draw_color_button(buf, (position) {color_button_x, 220}, COLOR_RED);
  draw_color_button(buf, (position) {color_button_x, 270}, COLOR_BROWN);
  draw_color_button(buf, (position) {color_button_x, 320}, COLOR_YELLOW);
  

  draw_plus_button(buf, (position) {other_buttons_x, 70}); // y = CANVAS_TOP_VISIBLE_LIMIT + (CANVAS_MARGIN - BUTTON_FRAME_HEIGHT) / 2
  draw_minus_button(buf, (position) {other_buttons_x, 120}); // y = previous_y() + (CANVAS_MARGIN - BUTTON_FRAME_HEIGHT) / 2
  
  
  draw_clear_canvas_button(buf, (position) {other_buttons_x, 320}); // y = CANVAS_BOTTOM_VISIBLE_LIMIT - (CANVAS_MARGIN - BUTTON_FRAME_HEIGHT)/2 - BUTTON_FRAME_HEIGHT
}
