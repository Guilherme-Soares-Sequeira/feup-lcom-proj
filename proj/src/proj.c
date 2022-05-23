/* LCF include */ 

#include <lcom/lcf.h>


/* device includes */

#include <lcom/video_gr.h>
#include <lcom/timer.h>
#include "devices/kbc/kbc.h"
#include "devices/kbc/mouse.h"
#include "devices/video/vbe.h"
#include "devices/video/video_gr.h"


/* utils include */

#include "utils/utils.h"


/* other includes */

#include <stdbool.h>
#include "cursor.h"
#include "xpm/cursor.xpm"


/* global variables */

/* keyboard */

extern int scancode_size;
extern int scancode_type;

extern uint8_t scancode;
extern uint8_t *scancodes;

extern bool ready, scancode_processed;

/* mouse */

struct packet mouse_packet;
extern bool mouse_ready;


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
  uint8_t keyboard_bit, mouse_bit;

  kbc_enable_data_report();

  /* subscribe interrupts */

  kbc_subscribe_int(&keyboard_bit);
  mouse_subscribe_int(&mouse_bit);

  /* video card initialization */

  vg_init(VBE_MODE_1024x768_INDEXED);
  // vg_init(VBE_MODE_1280x1024_FULL_COLOR);

  cursor_load();
  
  int ipc_status, r;
  message msg;

  bool run = true;

  while (run) {
    /* Get a request message. */
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(keyboard_bit)) {
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
          
          if (msg.m_notify.interrupts & BIT(mouse_bit)) {
            mouse_ih();

            if (mouse_ready) {
              cursor_move(mouse_packet.delta_x, mouse_packet.delta_y);
            }
          }
      }
    }

    clear_screen();
    vg_draw_rectangle(0, 0, 1024, 768, 63);
    cursor_draw();
    flip();
  }

  /* unsubscribe interrupts */

  kbc_unsubscribe_int();
  mouse_unsubscribe_int();

  /* disable data reporting */
  
  reset_kbc();

  /* exit graphics mode */

  vg_exit();

  return EXIT_SUCCESS;
}
