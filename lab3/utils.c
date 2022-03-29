#include "i8042.h"
#include <lcom/lcf.h>

#include <stdint.h>

int counter = 0;

int(util_sys_inb)(int port, uint8_t *value) {
    #ifdef LAB3
        counter++;
    #endif
    
    return sys_inb(port, (uint32_t *) value);
}