#include <lcom/lcf.h>

#include <stdbool.h>

#include "PS2.h"
#include "i8042.h"

int (mouse_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();
int (kbc_outbuf_full)();
struct packet (get_mouse_packet)();
int16_t (uint8_to_int16) (uint8_t uint8_val, bool sign);
