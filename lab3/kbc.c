#include <lcom/lcf.h>
#include <stdint.h>

#include "i8042.h"

#define  DELAY_US 20000

int      scancode_size;
int      scancode_type;

uint8_t  global_hook_id;
uint8_t  st_reg;
uint8_t* scancodes;

int32_t  used_ids = 0;

int(kbc_subscribe_int)(uint8_t *bit_no) {
  int hook_id; // random

  while (BIT(hook_id = (rand() % 32)) & used_ids)
    ;
  used_ids |= BIT(hook_id);

  *bit_no = (uint8_t) hook_id;

  int res = sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);

  global_hook_id = (uint8_t) hook_id;

  return res;
}

int(kbc_unsubscribe_int)() {
  int temp = global_hook_id;
  return sys_irqrmpolicy(&temp);
}

void (kbc_ih)() {
  uint8_t scancode = 0;

  scancode_size = 1;
  scancodes = (uint8_t*)malloc(sizeof(uint8_t)); // initialze array with size = 1

  util_sys_inb(KBC_OUT_BUF_STATUS, &st_reg);

  if (st_reg & KBC_STATUS_OK_MASK) 
    scancode_size = 0;
  
  if (st_reg & KBC_STATUS_OUTBUF_FULL) {
    util_sys_inb(KBC_OUT_BUF_SCAN, &scancode);
    
    if (scancode_size == 0) 
      return;
    
    scancodes[0] = scancode;
    scancode_size = 1;
  }

  if (scancodes[0] == KBC_SCAN_DOUBLE_BYTE || scancodes[0] == KBC_SCAN_TRIPLE_BYTE) {
    util_sys_inb(KBC_OUT_BUF_SCAN, &scancode);

    scancodes = (uint8_t*)realloc(scancodes, 2 * sizeof(uint8_t)); // reallocate memory

    scancodes[1] = scancode;
    scancode_size = 2;
  }

  if (scancodes[0] == KBC_SCAN_TRIPLE_BYTE) {
    util_sys_inb(KBC_OUT_BUF_SCAN, &scancode);

    scancodes = (uint8_t*)realloc(scancodes, 3 * sizeof(uint8_t)); // reallocate memory

    scancodes[2] = scancode;
    scancode_size = 3;
  }

  if (scancodes[scancode_size - 1] & BIT(7))
    scancode_type = KBC_SCANCODE_BREAK;
  else
    scancode_type = KBC_SCANCODE_MAKE;
}
