// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#define VBE_INTERFACE 0x10

#define VBE_SET_MODE 0x4F02

#define LINEAR_MODE BIT(14)

int (vbe_set_mode)(uint16_t mode);
