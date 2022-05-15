// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab4.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "mouse.h"

extern bool mouse_ready;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(mouse_test_packet)(uint32_t cnt) {
  uint8_t bit;
  mouse_enable_data_reporting();
  mouse_subscribe_int(&bit);

  int ipc_status, r;
  message msg;

  bool run = true;

  while (run) {
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status) && // found interrupt
        _ENDPOINT_P(msg.m_source) == HARDWARE &&
        msg.m_notify.interrupts & BIT(bit)) {

      mouse_ih();

      if (mouse_ready) { // need only to check if we are ready to print the scancode since errors should have been caught by the previous if statement

        struct packet data_packet = get_mouse_packet();

        mouse_print_packet(&data_packet);
        --cnt;

        if (cnt == 0) { // esc key was released
          run = false;
        }
      }
    }
  }

  mouse_unsubscribe_int();
  reset_kbc();

  return 1;
}

int(mouse_test_async)(uint8_t idle_time) {
  /* To be completed */
  printf("%s(%u): under construction\n", __func__, idle_time);
  return 1;
}

int(mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
  /* To be completed */
  printf("%s: under construction\n", __func__);
  return 1;
}

int(mouse_test_remote)(uint16_t period, uint8_t cnt) {
  /* This year you need not implement this. */
  printf("%s(%u, %u): under construction\n", __func__, period, cnt);
  return 1;
}
