#include <lcom/lcf.h>

#include "charset.h"
#include "draw_chat.h"
#include "../devices/kbc/i8042.h"

#define ENTER_MAKECODE 0x1c
#define TAB_MAKECODE 0x0f
#define CTRL_MAKECODE 0x1d
#define LEFT_SHIFT_MAKECODE 0x2a
#define RIGHT_SHIFT_MAKECODE 0x36
#define BACKSPACE_MAKECODE 0x0e

char default_charset[] = {NO_ADD_CHAR, NO_ADD_CHAR, '1', '2', '3', 
                          '4', '5', '6', '7', '8', 
                          '9', '0', '?', NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, 'q', 'w', 'e', 'r', 
                          't', 'y', 'u', 'i', 'o', 
                          'p', '+', NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          'a', 's', 'd', 'f', 'g', 
                          'h', 'j', 'k', 'l', 'c',
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, '~', 'z', 
                          'x', 'c', 'v', 'b', 'n', 
                          'm', ',', '.', '-', NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, ' ', NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, 
                          NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR, NO_ADD_CHAR};

void (process_scancode)(uint8_t* scancode, int scancode_size, int scancode_type) {

    if (scancode_size > 1) return;

    switch (scancode_type) {
        case KBC_SCANCODE_MAKE: {

            uint8_t code = scancode[0];

            if (code == BACKSPACE_MAKECODE)
                remove_char_from_current_text();
            else
                add_char_to_current_text(default_charset[code]);
        }
        case KBC_SCANCODE_BREAK: {

        }
    };
}