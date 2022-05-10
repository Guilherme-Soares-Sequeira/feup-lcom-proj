#include <lcom/lcf.h>

#include "i8042.h"
#include "mouse.h"

int32_t mouse_global_hook_id;

struct packet mouse_packet;

uint8_t counter = 0;

bool mouse_ready = false;

/* declared in LCF */

int (mouse_subscribe_int) (uint8_t *bit_no) {
  int hook_id = MOUSE_HOOK_ID;

  (*bit_no) = (uint8_t) hook_id;

  int res = sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, hook_id);

  mouse_global_hook_id = hook_id;
  
  return res;
}

int (mouse_unsubscribe_int)() {
  return sys_irqrmpolicy((int*) &mouse_global_hook_id);
}

void (mouse_ih)() {
  uint8_t byte = 0;
  
  if (!kbc_outbuf_full()) {
    util_sys_inb(KBC_OUT_BUF_SCAN, &byte);
    return;
  }

  util_sys_inb(KBC_OUT_BUF_SCAN, &byte);

  switch(counter) {
    case 0:
      if (! (byte & MOUSE_FBYTE) ) {
        mouse_ready = false;
        return;
      }
      mouse_packet.bytes[counter] = byte;
      mouse_packet.rb = byte & MOUSE_RB;
      mouse_packet.lb = byte & MOUSE_LB;
      mouse_packet.mb = byte & MOUSE_MB;
      mouse_packet.x_ov = byte & MOUSE_XOVFL;
      mouse_packet.y_ov = byte & MOUSE_YOVFL;

      
      mouse_packet.delta_x = 0;
      mouse_packet.delta_y = 0;
      
      break;
    case 1:
      bool sign = mouse_packet.bytes[0] & MOUSE_XSIGN;
      
      mouse_packet.bytes[1] = uint8_to_int16(byte, sign);

      break;

    case 2:
      bool sign = mouse_packet.bytes[0] & MOUSE_YSIGN;
      
      mouse_packet.bytes[2] = uint8_to_int16(byte, sign);
      break;    
  }
  counter == 2 ? counter = 0 : counter++;

}

int (kbc_outbuf_full)() {
  uint8_t st_reg = 0;
  util_sys_inb(KBC_OUT_BUF_STATUS, &st_reg);

  return (st_reg & KBC_STATUS_OUTBUF_FULL);
}

int16_t (uint8_to_int16) (uint8_t uint8_val, bool sign) {
  int16_t num = 0;
  if (sign == 0) { //positive
    return uint8_val;
  }
  else {
    uint8_t temp = UINT8_MAX - (uint8_val - 1);
    num = *((int8_t*) &(temp));
    return num;
  }
}