#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include <i8042.h>
#include <kbc.h>

// #define LAB3

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  uint8_t bit;
  kbc_subscribe_int(&bit);

  int ipc_status, r;
  message msg;

  bool run = true;

  while (run) {
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status) && 
        _ENDPOINT_P(msg.m_source) == HARDWARE && 
        msg.m_notify.interrupts & BIT(bit)) {
      uint8_t stat, data;
      util_sys_inb(KBC_OUT_BUF_STATUS, &stat);

      if (stat & KBC_STATUS_OUTBUF_FULL) {
        util_sys_inb(KBC_OUT_BUF_SCAN, &data);

        if ((stat & KBC_STATUS_OK_MASK) == 0)
          kbd_print_scancode(!(data & BIT(7)), 1, &data);

        if (data == 0x81)
          run = false;
      }
    }
  }

  kbc_unsubscribe_int(&bit);
  
  return 1;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
