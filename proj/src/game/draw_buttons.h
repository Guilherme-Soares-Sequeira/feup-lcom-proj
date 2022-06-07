#ifndef DRAW_BUTTONS_H
#define DRAW_BUTTONS_H

#include "../utils/position.h"
#include "../xpm/buttons/button_plus_size.xpm"

#include "pixel_buffer.h"
#include "element.h"

#define BUTTON_FRAME_WIDTH 40
#define BUTTON_FRAME_HEIGHT 40
#define BUTTON_FRAME_COLOR 7


void (draw_button_frame)(pixel_buffer const * const buf, position topleft_pos);

void (draw_color_button)(pixel_buffer const * const buf, position topleft_pos, uint8_t color);

void (load_button_xpms)();

void (draw_black_color_button)();

void (draw_blue_color_button)();

void (draw_green_color_button)();

void (draw_red_color_button)();

void (draw_brown_color_button)();

void (draw_yellow_color_button)();

void (draw_plus_button)();

void (draw_minus_button)();

void (draw_sel_line_button)();

void (draw_sel_square_button)();

void (draw_sel_circle_button)();

void (draw_sel_eraser_button)();

void (buttons_draw)();

#endif
