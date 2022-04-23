// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/video_gr.h>

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#include "vbe.h"

vbe_mode_info_t vg_mode_info;
void* vram;

bool indexed = false;

void (_get_mode_info)(in_port_t mode) { //TODO: implement this using sys_int86
  vbe_get_mode_info(mode, &vg_mode_info);
}

void (_map_memory)() {
  vram = 0;
  int r;
  struct minix_mem_range mr; /* physical memory range */
  unsigned int vram_base = vg_mode_info.PhysBasePtr; /* VRAM’s physical addresss */
  unsigned int vram_size = ceil(vg_mode_info.BitsPerPixel/8.0) * vg_mode_info.XResolution * vg_mode_info.YResolution; /* VRAM’s size, but you can use the frame-buffer size, instead */
  printf("%u\n", vram_size);
  /* Allow memory mapping */
  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;
  if((r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) != OK)
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
  /* Map memory */
  vram = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
  if(vram == MAP_FAILED)
    panic("couldn’t map video memory");
}

void* (vg_init)(in_port_t graphics_mode) {
  _get_mode_info(graphics_mode);
  _map_memory();

  struct reg86 r;
  memset(&r, 0, sizeof(r));

  r.intno = VBE_INTERFACE;
  r.ax = VBE_SET_MODE;
  r.bx = graphics_mode | LINEAR_MODE;

  if (sys_int86(&r) || r.al != 0x4F || r.ah != 0) return NULL;

  indexed = graphics_mode == 0x105;

  return vram;
}

#define COLOR_SIZE_MASK(x) (BIT(x) - 1)

int _bytes_per_pixel() {
  return (vg_mode_info.BitsPerPixel + vg_mode_info.LinRsvdMaskSize)/8;
}

int (vg_draw_pixel)(uint8_t* vram_base, uint16_t x, uint16_t y, uint32_t color) {

  if (indexed && color > 255) return 1;

  color &= COLOR_SIZE_MASK(vg_mode_info.BitsPerPixel);

  int bytes_per_pixel = _bytes_per_pixel();

  int pixel_offset = x + y * vg_mode_info.XResolution;
  int byte_offset = pixel_offset * bytes_per_pixel;

  uint8_t* pixel_start = vram_base + byte_offset;

  for (int j = 0; j < bytes_per_pixel; j++) {
    pixel_start[j] = color & 0xFF;
    color >>= 8;
  }

  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {

  if (indexed && color > 255) return 1;

  uint8_t* base = ((uint8_t*)vram);

  color &= COLOR_SIZE_MASK(vg_mode_info.BitsPerPixel);
  
  for (int i = 0; i < len; i++)
    if (vg_draw_pixel(base, x + i, y, color)) return 1;

  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {

  if (indexed && color > 255) return 1;

  color &= COLOR_SIZE_MASK(vg_mode_info.BitsPerPixel);

  for(int i = 0; i < height; i++)
    if (vg_draw_hline(x, y + i, width, color)) return 1;

  return 0;
}
