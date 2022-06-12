#include <lcom/lcf.h>
#include <math.h>

#include "draw_clock.h"
#include "canvas.h"
#include "../devices/video/graphics.h"
#include "../devices/rtc/rtc.h"
#include "../utils/color.h"

#include "../xpm/clock.xpm"

#include "text.h"

static xpm_image_t clock_xpm;

static position clock_pos = {
  H_RES - CANVAS_MARGIN - 40,
  V_RES - CANVAS_MARGIN - 40
};

static position clock_pos_center = {
  H_RES - CANVAS_MARGIN,
  V_RES - CANVAS_MARGIN
};

void (clock_load)() {
  clock_xpm = vg_load_xpm(xpm_clock);
}

void (clock_draw)() {
  const pixel_buffer *const buf = get_back_buffer();

  buf_draw_xpm(buf, clock_xpm, clock_pos);

  int hour = rtc_get_hours() % 12;
  int minute = rtc_get_minutes();
  int second = rtc_get_seconds();
  double hour_angle = M_PI * (hour + (minute/60.0)) / 6.0;
  position hour_pos = {
    clock_pos_center.x + 20 * sin(hour_angle),
    clock_pos_center.y - 20 * cos(hour_angle)
  };
  buf_draw_line(buf, clock_pos_center, hour_pos, COLOR_BLACK);

  double minute_angle = M_PI * (minute + (second/60.0)) / 30.0;
  int minute_pos_x = clock_pos_center.x + 32 * sin(minute_angle);
  int minute_pos_y = clock_pos_center.y - 32 * cos(minute_angle);
  position minute_pos = {minute_pos_x, minute_pos_y};
  buf_draw_line(buf, clock_pos_center, minute_pos, COLOR_BLACK);
}
