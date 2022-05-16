#ifndef UTILS_H
#define UTILS_H

#include <lcom/lcf.h>


/* masks used to fetch the LSB and MSB of a 16-bit integer */

#define LSB_MASK16 0x00FF
#define LSB_MASK32 0x000000FF
#define MSB_MASK16 0xFF00
#define MSB_MASK32 0XFF000000


int (util_get_LSB)(uint16_t val, uint8_t *lsb);

int (util_get_MSB)(uint16_t val, uint8_t *msb);

int (util_sys_inb)(int port, uint8_t *value);

#endif
