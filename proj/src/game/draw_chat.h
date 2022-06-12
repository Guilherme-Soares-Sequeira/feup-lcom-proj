#ifndef DRAW_CHAT_H
#define DRAW_CHAT_H

#include "../utils/position.h"

#include "pixel_buffer.h"
#include "element.h"

#define CHAR_SCALE 2

#define CHAT_HEIGHT (CHAR_HEIGHT * 2 * CHAR_SCALE/2)
#define INPUT_CHAR_SIZE 80

void (draw_text_input)(pixel_buffer const * const buf, position topleft_pos);

void (chat_draw)();

void (add_char_to_current_text)(char c);

void (clear_current_text)();

char* (get_current_text)();

void (remove_char_from_current_text)();

#endif
