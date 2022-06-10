#include <lcom/lcf.h>

#include "../devices/video/graphics.h"
#include "draw_chat.h"
#include "text.h"

int text_size = 0;
char text[INPUT_CHAR_SIZE + 1] = {0};
char *chat_messages[INPUT_CHAR_SIZE + 1] = {0};

void (draw_text_input)(pixel_buffer const * const buf, position topleft_pos) {
    buf_draw_rectangle(buf, (position) {topleft_pos.x, topleft_pos.y}, H_RES - CANVAS_MARGIN, CHAT_HEIGHT, COLOR_WHITE);
}

void (add_char_to_current_text)(char c) {

    if (text_size >= INPUT_CHAR_SIZE) return;

    text[text_size++] = c;
}

void (remove_char_from_current_text)() {
    if (text_size <= 0) return;

    text[--text_size] = 0;
}

void (chat_draw)() {

    const pixel_buffer *const buf = get_back_buffer();

    int chat_x = CANVAS_MARGIN / 2;
    int chat_y = V_RES - CANVAS_MARGIN/2 - CHAT_HEIGHT;

    draw_text_input(buf, (position) {chat_x, chat_y});

    text_draw(text, chat_x + 5, chat_y + 2, CHAR_SCALE, COLOR_BLACK, LEFT);
}

