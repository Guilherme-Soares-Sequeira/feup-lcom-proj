#include <lcom/lcf.h>

#include <stdbool.h>

#include "PS2.h"
#include "i8042.h"
#include "../../utils/utils.h"

#define mouse_packet_t struct packet

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

bool (kbc_mouse_data)();

bool (lb_is_pressed)();

struct packet (get_mouse_packet)();

void (reset_kbc)();

void (wait_for_inbuff_empty)();

void (write_command_to_mouse)(uint8_t command);

void (kbc_enable_data_report)();

uint8_t (mouse_command_feedback)();

int16_t(uint8_to_int16)(uint8_t uint8_val, bool sign);

bool (mouse_packet_ready)();
