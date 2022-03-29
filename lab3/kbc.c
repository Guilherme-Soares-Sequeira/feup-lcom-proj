#include <lcom/lcf.h>
#include <stdint.h>

#include "i8042.h"

#define DELAY_US 20000

uint8_t global_hook_id;

int32_t used_ids = 0;

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

int(kbc_unsubscribe_int)(uint8_t *bit_no) {
  return sys_irqrmpolicy((int *) &global_hook_id);
}
