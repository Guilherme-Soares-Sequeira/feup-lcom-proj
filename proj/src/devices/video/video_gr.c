// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/video_gr.h>

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  
  if (indexed && color > 255) return 1;

  if (x >= vg_mode_info.XResolution || x < 0 || y >= vg_mode_info.YResolution ||  y < 0)
    return 0;

  color &= COLOR_SIZE_MASK(vg_mode_info.BitsPerPixel);

  int bytes_per_pixel = _bytes_per_pixel();

  int pixel_offset = x + y * vg_mode_info.XResolution;
  int byte_offset = pixel_offset * bytes_per_pixel;

  uint8_t* pixel_start = (uint8_t*)vram + byte_offset;

  for (int j = 0; j < bytes_per_pixel; j++) {
    pixel_start[j] = color & 0xFF;
    color >>= 8;
  }

  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (int i = 0; i < len && x + i < vg_mode_info.XResolution; i++)
    if (vg_draw_pixel(x + i, y, color)) return 1;

  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for(int i = 0; i < height && y + i < vg_mode_info.YResolution; i++)
    if (vg_draw_hline(x, y + i, width, color)) return 1;

  return 0;
}

int (vg_draw_circle)(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
  int32_t top_left_x = x - radius;
  int32_t top_left_y = y - radius;
  int32_t max_distance = radius * radius;
  int32_t x32 = x, y32 = y; // So that calculations don't overflow
  
  for (int32_t i = top_left_x; i <= top_left_x + 2*radius; i++) {
      for (int32_t j = top_left_y; j <= top_left_y + 2*radius; j++) {
          if ((x32-i) * (x32-i) + (y32-j) * (y32-j) <= max_distance) {
              if (vg_draw_pixel(i, j, color)) {
                  return 1;
              }
          }
      }
  }

  return 0;
}

int (_vg_draw_line_low)(uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, uint16_t dx, uint16_t dy, int color) {
  int yi = 1;

  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }

  int D = 2*dy - dx;
  int y = from_y;

  for (int x = from_x; x <= to_x; x++) {
    if (vg_draw_pixel(x, y, color))
      return 1;

    if (D > 0) {
      y += yi;
      D += 2 * (dy - dx);
    } else
      D += 2 * dy;
  }

  return OK;
}

int (_vg_draw_line_high)(uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, uint16_t dx, uint16_t dy, int color) {
  int xi = 1;

  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }

  int D = 2*dx - dy;
  int x = from_x;

  for (int y = from_y; y <= to_y; y++) {
    if (vg_draw_pixel(x, y, color))
      return 1;

    if (D > 0) {
      x += xi;
      D += 2 * (dx - dy);
    } else
      D += 2 * dx;
  }

  return OK;
}

int (vg_draw_line)(uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, int color) {
  uint16_t dx = to_x - from_x;
  uint16_t dy = to_y - from_y;
  if (abs(dy) < abs(dx))
    if (from_x > to_x)
      return _vg_draw_line_low(to_x, to_y, from_x, from_y, dx, dy, color);
    else
      return _vg_draw_line_low(from_x, from_y, to_x, to_y, dx, dy, color);
  else
    if (from_y > to_y)
      return _vg_draw_line_high(to_x, to_y, from_x, from_y, dx, dy, color);
    else
      return _vg_draw_line_high(from_x, from_y, to_x, to_y, dx, dy, color);
}

xpm_image_t (vg_load_xpm) (const xpm_map_t map) {
  xpm_image_t info;
  xpm_load(map, XPM_INDEXED, &info);
  return info;
}

int (vg_draw_xpm)(const xpm_image_t xpm_info, uint16_t x, uint16_t y) {
  uint8_t* bytes = xpm_info.bytes;
  
  for (unsigned long int i = 0; i < (unsigned long) xpm_info.size; i++) {
    if (vg_draw_pixel(
      x + (i % xpm_info.width), y + (i / xpm_info.height), (uint32_t) *(bytes + i))
      ) 
        return 1;    
  }
  
  return OK;
}

void getRGB(uint32_t color, uint8_t* r, uint8_t* g, uint8_t* b) {
  *r = (color >> vg_mode_info.RedFieldPosition)   & COLOR_SIZE_MASK(vg_mode_info.RedMaskSize);
  *g = (color >> vg_mode_info.GreenFieldPosition) & COLOR_SIZE_MASK(vg_mode_info.GreenMaskSize);
  *b = (color >> vg_mode_info.BlueFieldPosition)  & COLOR_SIZE_MASK(vg_mode_info.BlueMaskSize);
}

uint32_t makeRGB(uint8_t r, uint8_t g, uint8_t b) {
  return 0 | ((r & COLOR_SIZE_MASK(vg_mode_info.RedMaskSize))   << vg_mode_info.RedFieldPosition) |          ((g & COLOR_SIZE_MASK(vg_mode_info.GreenMaskSize)) << vg_mode_info.GreenFieldPosition) |          ((b & COLOR_SIZE_MASK(vg_mode_info.BlueMaskSize))  <<  vg_mode_info.BlueFieldPosition);
}

uint32_t getIndexedColor(uint32_t index, int no_rectangles, int col, int row, int step) {
  return (index + (row * no_rectangles + col) * step) % (1 << vg_mode_info.BitsPerPixel);
}

uint32_t getDirectColor(uint32_t color, int no_rectangles, int col, int row, int step) {

    uint8_t r, g, b;
    getRGB(color, &r, &g, &b);

    r = (r + col * step) % (1 << vg_mode_info.RedMaskSize);
  	g = (g + row * step) % (1 << vg_mode_info.GreenMaskSize);
  	b = (b + (col + row) * step) % (1 << vg_mode_info.BlueMaskSize);	

    return makeRGB(r, g, b);
}

int vg_draw_pattern(uint8_t no_rectangles, uint32_t first, uint8_t step) {

  int size_x = vg_mode_info.XResolution / no_rectangles;
  int size_y = vg_mode_info.YResolution / no_rectangles;

  for (int y = 0; y < no_rectangles; ++y)
    for (int x = 0; x < no_rectangles; ++x) {

      uint32_t color = (indexed ? getIndexedColor : getDirectColor)(first, no_rectangles, x, y, step);

      if (vg_draw_rectangle(x * size_x, y * size_y, size_x, size_y, color)) return 1;
    }

  return 0;
}

void (clear_screen)() {
  memset(vram, 0, ceil(vg_mode_info.BitsPerPixel/8.0) * vg_mode_info.XResolution * vg_mode_info.YResolution);
}
