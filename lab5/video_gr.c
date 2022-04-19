// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/video_gr.h>

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "vbe.h"

vbe_mode_info_t mode_info;
void* vram;

void (_get_mode_info)(in_port_t mode) {
  vbe_get_mode_info(mode, &mode_info);
}

void (_map_memory)() {
  vram = 0;
  int r;
  struct minix_mem_range mr; /* physical memory range */
  unsigned int vram_base = mode_info.PhysBasePtr; /* VRAM’s physical addresss */
  unsigned int vram_size = ceil(mode_info.BitsPerPixel/8.0) * mode_info.XResolution * mode_info.YResolution; /* VRAM’s size, but you can use the frame-buffer size, instead */
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
  sys_int86(&r);

  if (r.al != 0x4F || r.ah != 0) return NULL;

  return vram;
}
