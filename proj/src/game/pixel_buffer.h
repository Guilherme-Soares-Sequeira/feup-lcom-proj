#include <lcom/lcf.h>

#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint16_t h_res;
  uint16_t v_res;

  uint32_t buffer_size;
  
  uint8_t bytes_per_pixel;
  
  void* buffer_start;
} pixel_buffer;

pixel_buffer new_pixel_buffer(uint16_t h_res, uint16_t v_res, uint8_t bytes_per_pixel);