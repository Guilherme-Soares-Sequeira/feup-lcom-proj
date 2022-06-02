#ifndef TEXT_H
#define TEXT_H

#include <lcom/lcf.h>
#include <lcom/video_gr.h>

#define CHAR_WIDTH 6
#define CHAR_HEIGHT 11
#define FONT_WIDTH 16
#define FONT_HEIGHT 16

typedef enum {
  LEFT,
  CENTER,
  RIGHT
} text_alignment_t;

void (text_load)();

void (text_draw)(char* text, int16_t x, int16_t y, int16_t scale, int color, text_alignment_t alignment);

#endif
