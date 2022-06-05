#ifndef DRAW_BUTTONS_H
#define DRAW_BUTTONS_H

#include "../utils/position.h"

#define BUTTON_FRAME_WIDTH 40
#define BUTTON_FRAME_HEIGHT 40
#define BUTTON_FRAME_COLOR 7

void draw_button_frame(position topleft_pos);

void draw_color_button(position topleft_pos, uint8_t color);

void draw_plus_button(position topleft_pos, uint8_t _);

void draw_minus_button(position topleft_pos, uint8_t _);

void draw_sel_line_button(position topleft_pos, uint8_t _);

void draw_sel_square_button(position topleft_pos, uint8_t _);

void draw_sel_circle_button(position topleft_pos, uint8_t _);

void draw_sel_eraser_button(position topleft_pos, uint8_t _);

#endif
