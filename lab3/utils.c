#include "i8042.h"
#include <lcom/lcf.h>

#include <stdint.h>

#define LSB_MASK 0x000000FF

int counter = 0;

uint8_t (get_LSB)(uint32_t num) {
	return (uint8_t) num & LSB_MASK;
}

int(util_sys_inb)(int port, uint8_t *value) {
  #ifdef LAB3
			counter++;
	#endif
    
	uint32_t temp = 0;
	int ret = sys_inb(port, &temp);
	*value = get_LSB(temp);
	return ret; 
}
