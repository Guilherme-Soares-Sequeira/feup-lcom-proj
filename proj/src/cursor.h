#ifndef CURSOR_H
#define CURSOR_H

#include <lcom/lcf.h>
#include <lcom/video_gr.h>
#include <stdbool.h>

#include "devices/video/video_gr.h"


/* loads the xpm image of the cursor */
void (cursor_load)();

/* moves the cursor around the screen */
void (cursor_move)(int16_t delta_x, int16_t delta_y);

/* assigns a new value to the left button of the cursor */
void (cursor_set_lb)(bool new_lb);

/* draws the cursor on screen */
void (cursor_draw)();

void (cursor_clear)();

/* indicates whether the left button is pressed or not */
bool (cursor_lb_pressed)();

#endif
