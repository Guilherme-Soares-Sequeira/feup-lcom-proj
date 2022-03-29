#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define KBC_IRQ 1 /**< @brief KBC IRQ line */

#define KBC_IN_BUF_DATA 0x60
#define KBC_IN_BUF_CMD 0x64
#define KBC_OUT_BUF_SCAN 0x60
#define KBC_OUT_BUF_STATUS 0x64

#define KBC_STATUS_OK_MASK (BIT(7) | BIT(6))
#define KBC_STATUS_INBUF_FULL (BIT(1))
#define KBC_STATUS_OUTBUF_FULL (BIT(0))

#define KBC_SCAN_DOUBLE_BYTE (0xE0) 

#endif