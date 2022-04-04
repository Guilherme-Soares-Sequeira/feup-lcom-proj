#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "kbc.h"

extern int scancode_size;
extern int scancode_type;

extern uint8_t global_hook_id;
extern uint8_t scancode;
extern uint8_t st_reg;
extern uint8_t* scancodes;

extern int32_t used_ids;

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

    if (is_ipc_notify(ipc_status) && // found interrupt 
        _ENDPOINT_P(msg.m_source) == HARDWARE && 
        msg.m_notify.interrupts & BIT(bit)) {
          
      kbc_ih();
      
      if (scancode_size == 0) { //check with professor
        run = false;
        free(scancodes);
        continue;
      }

      if ((st_reg & KBC_STATUS_OK_MASK) == 0) 
        kbd_print_scancode(scancode_type, scancode_size, scancodes);
      
      if (scancodes[0] == ESC_KEY_BREAK_CODE) // esc key was released
        run = false;
          
      free(scancodes); 
    }
  }

  kbc_unsubscribe_int();
  
  return 1;
}

int(kbd_test_poll)() {
  bool run = true;

  while (run) {
    if (kbc_outbuf_full()) {
      kbc_ih();
      
      if (scancode_size == 0) {
        run = false;
        free(scancodes);
        continue;
      }

      if ((st_reg & KBC_STATUS_OK_MASK) == 0) 
        kbd_print_scancode(scancode_type, scancode_size, scancodes);
      
      if (scancodes[0] == ESC_KEY_BREAK_CODE) // esc key was released
        run = false;
          
      free(scancodes); 
    }

    tickdelay(micros_to_ticks(DELAY_US));  
  }
  
  kbc_enable_int();
  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
