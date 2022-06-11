#ifndef DRAW_BUTTONS_H
#define DRAW_BUTTONS_H

#include "../utils/position.h"
#include "../xpm/buttons/button_plus_size.xpm"
#include "../xpm/buttons/button_minus_size.xpm"
#include "../xpm/buttons/button_clear_canvas.xpm"

#include "pixel_buffer.h"
#include "element.h"

#define BUTTON_FRAME_WIDTH 40
#define BUTTON_FRAME_HEIGHT 40
#define BUTTON_FRAME_COLOR 7


void (draw_button_frame)(pixel_buffer const * const buf, position topleft_pos);

int (draw_color_button)(pixel_buffer const * const buf, position topleft_pos, uint8_t color);

void (load_button_xpms)();

void (draw_plus_button)(pixel_buffer const * const buf, position topleft_pos);

void (draw_minus_button)(pixel_buffer const * const buf, position topleft_pos);

int (draw_sel_line_button)(pixel_buffer const * const buf, position topleft_pos);

int (draw_sel_square_button)(pixel_buffer const * const buf, position topleft_pos);

int (draw_sel_circle_button)(pixel_buffer const * const buf, position topleft_pos);

void (draw_sel_eraser_button)(pixel_buffer const * const buf, position topleft_pos);

void (draw_clear_canvas_button)(pixel_buffer const * const buf, position topleft_pos);

int (buttons_draw)();

#endif
