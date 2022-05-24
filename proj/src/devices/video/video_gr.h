#include <lcom/lcf.h>

int (vg_draw_circle)(uint16_t x, uint16_t y, uint16_t radius, uint32_t color);
int (vg_draw_line)(uint16_t from_x, uint16_t from_y, uint16_t to_x, uint16_t to_y, int color);
int (vg_draw_xpm)(const xpm_image_t xpm_info, uint16_t x, uint16_t y);
xpm_image_t (vg_load_xpm) (const xpm_map_t map);
void (clear_screen)();
void (flip)();
