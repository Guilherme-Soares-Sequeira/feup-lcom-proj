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

/**
 * @brief subscribes to RTC interrupts and puts the given bit in bit_no
 * 
 * @param[in] bit_no Bit number of the RTC interrupt messages
 */
int(rtc_subscribe_int)(uint8_t *bit_no);

/**
 * @brief unsubscribes RTC interrupts
 */
int(rtc_unsubscribe_int)();

/**
 *  @brief interrupt handler for the RTC
 */
void(rtc_int_handler)();

/**
 *  @brief sets up the RTC with some default operation values
 */
void(setup_update_interrupts)();

/**
 *  @brief reads the value present in the given RTC register
 *  
 *  @param reg_no the register number
 * 
 *  @return the value present in the given RTC register
 */
uint8_t(read_from_reg)(uint8_t reg_no);

/**
 *  @brief writes the given value to the given RTC register
 *  
 *  @param reg_no the register number
 *  @param data the data to write
 */
void(write_to_reg)(uint8_t reg_no, uint8_t data);

/**
 *  @brief get current seconds
 * 
 *  @return the current RTC seconds
 */
unsigned short(rtc_get_seconds)();

/**
 *  @brief get current minutes
 * 
 *  @return the current RTC minutes
 */
unsigned short(rtc_get_minutes)();

/**
 *  @brief get current hours
 * 
 *  @return the current RTC hours
 */
unsigned short(rtc_get_hours)();

/**
 *  @brief get a formatted representation of the current time
 * 
 *  @return the current RTC time in a formatted string
 */
char *(rtc_get_formatted_time) ();

#endif
