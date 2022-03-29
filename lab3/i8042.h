#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define KBC_IRQ 1 /**< @brief KBC IRQ line */

#define KBC_IN_BUF_DATA 0x60
#define KBC_IN_BUF_CMD 0x64
#define KBC_OUT_BUF_SCAN 0x60
#define KBC_OUT_BUF_STATUS 0x64

#endif