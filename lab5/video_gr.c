// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/video_gr.h>

#include <stdint.h>
#include <stdio.h>

#include "vbe.h"

void* (vg_init)(in_port_t graphics_mode) {
  struct reg86 r;
  memset(&r, 0, sizeof(r));

  r.intno = VBE_INTERFACE;
  r.ax = VBE_SET_MODE;
  r.bx = graphics_mode | LINEAR_MODE;
  sys_int86(&r);

  return NULL;
}
