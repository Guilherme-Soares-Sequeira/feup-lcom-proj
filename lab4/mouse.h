#include <lcom/lcf.h>

#include <stdbool.h>

#include "PS2.h"
#include "i8042.h"

#define DISABLE_DATA_REPORTING_CMD 0xF5
#define SET_STREAMMODE_CMD 0XEA

int (mouse_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();

bool (kbc_outbuf_full)();
struct packet (get_mouse_packet)();
int16_t (uint8_to_int16) (uint8_t uint8_val, bool sign);
void (reset_kbc)();
void (write_command_to_mouse) (uint8_t command);
