#include "ui.h"

void (draw_menu)(){
  pixel_buffer const * const back_buf = get_back_buffer();
  buf_draw_rectangle(back_buf, (position) {0, 0}, CANVAS_LEFT_VISIBLE_LIMIT, CANVAS_BOTTOM_VISIBLE_LIMIT, COLOR_BLUE);
  buf_draw_rectangle(back_buf, (position) {0, CANVAS_BOTTOM_VISIBLE_LIMIT - 60}, CANVAS_RIGHT_VISIBLE_LIMIT, 60, COLOR_BLUE);

  buf_draw_rectangle(back_buf, (position) {0, CANVAS_TOP_VISIBLE_LIMIT}, CANVAS_LEFT_VISIBLE_LIMIT, CANVAS_BOTTOM_VISIBLE_LIMIT - 120, COLOR_BLUE);
  buf_draw_rectangle(back_buf, (position) {CANVAS_RIGHT_VISIBLE_LIMIT - 60, CANVAS_TOP_VISIBLE_LIMIT}, 60, CANVAS_BOTTOM_VISIBLE_LIMIT - 120, COLOR_BLUE);
  buttons_draw();
}
