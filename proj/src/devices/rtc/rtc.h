#ifndef RTC_H
#define RTC_H

#define RTC_IRQ 0x8

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71

#define RTC_SECONDS_REG 0
#define RTC_SECONDS_ALARM_REG 1
#define RTC_MINUTES_REG 2
#define RTC_MINUTES_ALARM_REG 3
#define RTC_HOURS_REG 4
#define RTC_HOURS_ALARM_REG 5

#define RTC_CTRL_REG_A 10
#define RTC_CTRL_REG_B 11
#define RTC_CTRL_REG_C 12
#define RTC_CTRL_REG_D 13

#define ENABLE_UPDATE_INTERRUPT BIT(4)
#define BINARY_COUNTING_MODE BIT(2)
#define HOUR_RANGE_24H BIT(1)
#define DST BIT(0)

#define IQRF BIT(7)
#define UPDATE_INT_FLAG BIT(4)

int (rtc_subscribe_int)(uint8_t *bit_no);

int (rtc_unsubscribe_int)();

void (rtc_int_handler)();

void (setup_update_interrupts)();

uint8_t (read_from_register)(uint8_t reg_no);
void (write_to_reg)(uint8_t reg_no, uint8_t data);

unsigned short (rtc_get_seconds)();
unsigned short (rtc_get_minutes)();
unsigned short (rtc_get_hours)();

char* (rtc_get_formatted_time)();

#endif
