#include "../devices/video/graphics.h"
#include "draw_buttons.h"

void draw_button_frame(position topleft_pos) {
  vg_draw_hline(topleft_pos.x, topleft_pos.y, BUTTON_FRAME_WIDTH, BUTTON_FRAME_COLOR);
  vg_draw_hline(topleft_pos.x, topleft_pos.y + 1, BUTTON_FRAME_WIDTH, BUTTON_FRAME_COLOR);
  vg_draw_hline(topleft_pos.x, topleft_pos.y + BUTTON_FRAME_HEIGHT - 2, BUTTON_FRAME_COLOR);
  vg_draw_hline(topleft_pos.x, topleft_pos.y + BUTTON_FRAME_HEIGHT - 1, BUTTON_FRAME_WIDTH, BUTTON_FRAME_COLOR);

  vg_draw_vline()
}

void draw_color_button(position topleft_pos, uint8_t color) {
  
}

void draw_plus_button(position topleft_pos, uint8_t _) {

}

void draw_minus_button(position topleft_pos, uint8_t _) {

}

void draw_sel_line_button(position topleft_pos, uint8_t _) {

}

void draw_sel_square_button(position topleft_pos, uint8_t _) {

}

void draw_sel_circle_button(position topleft_pos, uint8_t _) {

}

void draw_sel_eraser_button(position topleft_pos, uint8_t _) {
  
}