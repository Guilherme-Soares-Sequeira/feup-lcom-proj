#ifndef __KBC_H
#define __KBC_H

#include <stdint.h>

int(kbc_subscribe_int)(uint8_t *bit_no);

int(kbc_unsubscribe_int)(uint8_t *bit_no);

#endif
