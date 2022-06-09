#ifndef CANVAS_H
#define CANVAS_H

#include <lcom/lcf.h>

#include "pixel_buffer.h"
#include "../devices/video/video_gr.h"
#include "../devices/video/graphics.h"
#include "../utils/color.h"
#include "cursor.h"

#define CANVAS_MARGIN 60
#define CANVAS_WIDTH (H_RES - CANVAS_MARGIN * 2)
#define CANVAS_HEIGHT (370)

#define CANVAS_TOP_VISIBLE_LIMIT CANVAS_MARGIN 
#define CANVAS_BOTTOM_VISIBLE_LIMIT (CANVAS_MARGIN + CANVAS_HEIGHT)
#define CANVAS_LEFT_VISIBLE_LIMIT CANVAS_MARGIN
#define CANVAS_RIGHT_VISIBLE_LIMIT (H_RES - CANVAS_MARGIN)

#define CANVAS_BYPP 1

void (canvas_load)(); /* loads the canvas */

pixel_buffer const * (get_canvas_buffer)();

void (canvas_draw)(); /* draws the canvas */

void (canvas_fill)(uint8_t color); /* fills the canvas with a color */

void (canvas_clear)(); /* fills the canvas with a white color */

void (canvas_mouse_handler)(uint8_t _);

int (canvas_draw_pencil_circle)();

int (canvas_draw_pencil_square)();

void (canvas_exit)(); /* frees the memory allocated to the canvas */


#endif
