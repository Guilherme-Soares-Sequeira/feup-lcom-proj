#include "../devices/video/graphics.h"
#include "draw_buttons.h"

/* button xpms */

static xpm_image_t button_plus;


xpm_image_t (get_button_plus)(){ return button_plus; }

void (load_button_xpms)() {
  button_plus = vg_load_xpm(xpm_button_plus);
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

void (draw_black_color_button)() {
  draw_color_button(get_back_buffer(), (position) {20, 10}, COLOR_BLACK);
}

void (draw_blue_color_button)() {
  draw_color_button(get_back_buffer(), (position) {70, 10}, COLOR_BLUE);
}

void (draw_green_color_button)() {
  draw_color_button(get_back_buffer(), (position) {120, 10}, COLOR_GREEN);
}

void (draw_red_color_button)() {
  draw_color_button(get_back_buffer(), (position) {170, 10}, COLOR_RED);
}

void (draw_brown_color_button)() {
  draw_color_button(get_back_buffer(), (position) {220, 10}, COLOR_BROWN);
}

void (draw_yellow_color_button)() {
  draw_color_button(get_back_buffer(), (position) {270, 10}, COLOR_YELLOW);
}

void (draw_plus_button)() {
  buf_draw_xpm(get_back_buffer(), button_plus, (position) {10, 50});
}

void (draw_minus_button)() {

}

void (draw_sel_line_button)() {

}

void (draw_sel_square_button)() {

}

void (draw_sel_circle_button)() {

}

void (draw_sel_eraser_button)() {
  
}

void (buttons_draw)() {
  draw_black_color_button();
  draw_blue_color_button();
  draw_green_color_button();
  draw_red_color_button();
  draw_brown_color_button();
  draw_yellow_color_button();
  draw_plus_button();
}
