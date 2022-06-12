#ifndef DRAW_CLOCK_H
#define DRAW_CLOCK_H

#include "../devices/rtc/rtc.h"

#define HOUR_HANDLE_LENGTH 20
#define MINUTE_HANDLE_LENGTH 32

void (clock_load)();
void (clock_draw)();

#endif
