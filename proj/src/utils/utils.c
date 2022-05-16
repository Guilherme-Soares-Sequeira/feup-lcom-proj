#include "utils.h"
#include <minix/sysutil.h>

int (util_get_LSB)(uint16_t val, uint8_t *lsb) {
  *lsb = (uint8_t) (val & LSB_MASK16);
  return OK;
}

int (util_get_MSB)(uint16_t val, uint8_t *msb) {
  *msb = (uint8_t) ((val & MSB_MASK16) >> 8);
  return OK;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t temp = 0;

  int ret = sys_inb(port, &temp);

  *value = (uint8_t) temp & LSB_MASK32;

  return ret;
}