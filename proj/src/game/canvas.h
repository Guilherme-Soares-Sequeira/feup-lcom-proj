#ifndef CANVAS_H
#define CANVAS_H

#include <lcom/lcf.h>

#include "pixel_buffer.h"

#define CANVAS_TOP_VISIBLE_LIMIT 30 
#define CANVAS_LEFT_VISIBLE_LIMIT 30
#define CANVAS_RIGHT_VISIBLE_LIMIT 770
#define CANVAS_BOTTOM_VISIBLE_LIMIT 340


void (canvas_init)();

void (canvas_fill)(uint8_t color);

void (canvas_clear)();

#endif
