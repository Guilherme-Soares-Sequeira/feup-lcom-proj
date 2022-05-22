/* LCF include */ 

#include <lcom/lcf.h>


/* device includes */

#include <lcom/video_gr.h>
#include <lcom/timer.h>
#include "devices/kbc/kbc.h"
#include "devices/kbc/mouse.h"
#include "devices/video/vbe.h"


/* utils include */

#include "utils/utils.h"


/* other includes */

#include <stdbool.h>


/* global variables */

/* keyboard */

extern int scancode_size;
extern int scancode_type;

extern uint8_t scancode;
extern uint8_t *scancodes;

extern bool ready, scancode_processed;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(proj_main_loop)(int argc, char* argv[]) {
  uint8_t keyboard_bit;

  /* subscribe interrupts */

  kbc_subscribe_int(&keyboard_bit);

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
        msg.m_notify.interrupts & BIT(keyboard_bit)) {

      kbc_ih();
      
      if (scancode_size == 0) { 
        scancode_processed = true;
        continue;
      }

      if (ready) {
        scancode_processed = true;

        if (scancodes[0] == ESC_KEY_BREAK) { 
          run = false;
          free(scancodes);
        }   
      }      
    }
  }

  /* unsubscribe interrupts */

  kbc_unsubscribe_int();

  return EXIT_SUCCESS;
}
