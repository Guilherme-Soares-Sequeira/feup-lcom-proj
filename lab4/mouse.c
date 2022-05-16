#include <lcom/lcf.h>
#include <lcom/lab4.h>
#include <lcom/utils.h>

#include <stdbool.h>

#include "i8042.h"
#include "mouse.h"

int32_t mouse_global_hook_id;

struct packet mouse_packet;

uint8_t counter = 0;

bool mouse_ready = false;

/* declared in LCF */

struct packet(get_mouse_packet)() {
  return mouse_packet;
}

int(mouse_subscribe_int)(uint8_t *bit_no) {
  int hook_id = MOUSE_HOOK_ID;

  (*bit_no) = (uint8_t) hook_id;

  int res = sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);

  mouse_global_hook_id = hook_id;

  return res;
}

int(mouse_unsubscribe_int)() {
  return sys_irqrmpolicy((int *) &mouse_global_hook_id);
}

void(mouse_ih)() {
  uint8_t byte = 0;

  bool obf_full = kbc_outbuf_full();

  util_sys_inb(KBC_OUT_BUF_SCAN, &byte);
  if (!obf_full)
    return;

  switch (counter) {
    case 0:
      if (!(byte & MOUSE_FBYTE)) {
        mouse_ready = false;
        return;
      }

      mouse_packet.rb = byte & MOUSE_RB;
      mouse_packet.lb = byte & MOUSE_LB;
      mouse_packet.mb = byte & MOUSE_MB;
      mouse_packet.x_ov = byte & MOUSE_XOVFL;
      mouse_packet.y_ov = byte & MOUSE_YOVFL;

      mouse_packet.delta_x = 0;
      mouse_packet.delta_y = 0;

      break;
    case 1: {
      bool sign = mouse_packet.bytes[0] & MOUSE_XSIGN;

      mouse_packet.delta_x = uint8_to_int16(byte, sign);
      break;
    }
    case 2: {
      bool sign = mouse_packet.bytes[0] & MOUSE_YSIGN;

      mouse_packet.delta_y = uint8_to_int16(byte, sign);
      break;
    }
  }
  mouse_packet.bytes[counter] = byte;
  counter = (counter + 1) % (sizeof(mouse_packet.bytes));

  mouse_ready = counter == 0; // when we catch a 0 at this point, we know we have successfully parsed 3 bytes
}

void (kbc_enable_data_report) () {
  wait_for_inbuff_empty();
  write_command_to_mouse(ENABLE_DATA_REPORTING_CMD);
}

bool(kbc_outbuf_full)() {
  uint8_t st_reg = 0;
  util_sys_inb(KBC_OUT_BUF_STATUS, &st_reg);

  return (st_reg & (KBC_STATUS_OUTBUF_FULL | BIT(5)));
}

int16_t(uint8_to_int16)(uint8_t uint8_val, bool sign) {
  return ((sign ? 0xFF : 0x00) << 8) | uint8_val;
}

void(reset_kbc)() {
  write_command_to_mouse(DISABLE_DATA_REPORTING_CMD);
  return;
}


void(wait_for_inbuff_empty)() {
  uint8_t status_reg;

  do {
    tickdelay(micros_to_ticks(20000));
    status_reg = 0;
    util_sys_inb(KBC_OUT_BUF_STATUS, &status_reg);
  } while (status_reg & KBC_STATUS_INBUF_FULL);

  return;
}

uint8_t(mouse_command_feedback)() {
  uint8_t byte = 0;

  util_sys_inb(KBC_OUT_BUF_SCAN, &byte);

  return byte;
}

void(write_command_to_mouse)(uint8_t command) {
  uint8_t feedback = 0;

  uint8_t temp = 0;
  
  do {
    wait_for_inbuff_empty();

    sys_outb(KBC_IN_BUF_CMD, WRITE_BYTE_TO_MOUSE);

    wait_for_inbuff_empty();

    sys_outb(KBC_IN_BUF_DATA, command);

    tickdelay(micros_to_ticks(25000));

    feedback = mouse_command_feedback();

    temp++;
  } while (feedback != MOUSE_ACK && feedback != MOUSE_ERROR && temp < 2); //technically should never run more than twice

  if (feedback != MOUSE_ACK) {
    fprintf(stderr, "%s failed while trying to execute command %x\n", __func__, command);
  }
}
