#ifndef POSITION_H
#define POSITION_H

#include <lcom/lcf.h>

/**
 * @brief a struct to represent an entity's position on screen by using (x, y) coordinates
 * 
 */
typedef struct {
  int16_t x;
  int16_t y;
} position;

#endif
