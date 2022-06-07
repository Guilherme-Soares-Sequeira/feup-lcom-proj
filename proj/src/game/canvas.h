#ifndef CANVAS_H
#define CANVAS_H

#include <lcom/lcf.h>

#include "pixel_buffer.h"
#include "../devices/video/video_gr.h"
#include "../devices/video/graphics.h"
#include "../utils/color.h"
#include "cursor.h"

#define CANVAS_TOP_VISIBLE_LIMIT 60 
#define CANVAS_BOTTOM_VISIBLE_LIMIT 370
#define CANVAS_LEFT_VISIBLE_LIMIT 60
#define CANVAS_RIGHT_VISIBLE_LIMIT 740

#define CANVAS_BYPP 1

void (canvas_load)(); /* loads the canvas */

pixel_buffer const * (get_canvas_buffer)();

void (canvas_draw)(); /* draws the canvas */

void (canvas_fill)(uint8_t color); /* fills the canvas with a color */

void (canvas_clear)(); /* fills the canvas with a white color */

void (canvas_mouse_handler)();

int (canvas_draw_pencil_circle)();

int (canvas_draw_pencil_square)();

void (canvas_exit)(); /* frees the memory allocated to the canvas */


#endif
