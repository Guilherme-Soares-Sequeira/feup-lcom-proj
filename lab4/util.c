#include <lcom/lcf.h>
#include <lcom/utils.h>

#define LSB_MASK 0xFF

uint8_t (get_LSB)(uint32_t num) {
	return (uint8_t) num & LSB_MASK;
}

int(util_sys_inb)(int port, uint8_t *value) {
	uint32_t temp = 0;
	int ret = sys_inb(port, &temp);
	*value = get_LSB(temp);
	return ret; 
}
