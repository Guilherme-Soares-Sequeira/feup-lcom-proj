#ifndef POSITION_H
#define POSITION_H

#include <lcom/lcf.h>

/**
 * @brief a struct to represent an entity's position on screen by using (x, y) coordinates
 * 
 */
typedef struct {
  uint16_t x;
  uint16_t y;
} position;

#endif
