/* LCF include */ 

#include <lcom/lcf.h>


/* device includes */

#include <lcom/video_gr.h>
#include <lcom/timer.h>
#include "devices/kbc/kbc.h"
#include "devices/kbc/mouse.h"
#include "devices/video/vbe.h"
#include "devices/video/video_gr.h"
#include "devices/timer/timer.h"


/* utils include */

#include "utils/utils.h"
#include "utils/color.h"


/* other includes */

#include <stdbool.h>
#include "game/cursor.h"
#include "xpm/cursor.xpm"
#include "game/canvas.h"
#include "game/text.h"
#include "game/element.h"
#include "game/ui.h"
#include "game/charset.h"

/* global variables */

/* keyboard */

extern uint8_t *scancodes;

#define FPS 60

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

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
  uint8_t keyboard_bit, mouse_bit, timer_bit;

  kbc_enable_data_report();

  /* subscribe interrupts */

  timer_subscribe_int(&timer_bit);
  kbc_subscribe_int(&keyboard_bit);
  mouse_subscribe_int(&mouse_bit);

  /* timer initialization */ 

  timer_set_frequency(0, FPS); //USE ONLY TO INCREASE FPS to more than 60    

  /* video card initialization */

  // vg_init(VBE_MODE_1024x768_INDEXED);
  vg_init(VBE_MODE_1024x768_INDEXED);
  // vg_init(VBE_MODE_1280x1024_FULL_COLOR);

  load_backbuffer();
  cursor_load();
  canvas_load();
  text_load();
  load_button_xpms();
  load_ie_drawing();

  int ipc_status, r;
  message msg;

  interactive_element* drawing_ies = get_drawing_ies();
  uint8_t num_ies = get_number_of_drawing_ies();

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
          if (msg.m_notify.interrupts & BIT(timer_bit)) {
            timer_int_handler();

            clear_screen(COLOR_BLUE);
            canvas_draw();
            draw_menu();
            
            cursor_draw();

            flip();
          }

          if (msg.m_notify.interrupts & BIT(mouse_bit)) {
            mouse_ih();

            if (mouse_packet_ready()) {

              mouse_packet_t mouse_packet = get_mouse_packet();

              cursor_move(mouse_packet.delta_x, mouse_packet.delta_y);
              
              if (mouse_packet.lb) {
                if (is_hovered(drawing_ies[0])) {
                  drawing_ies[0].mouse_event_handler(drawing_ies[0].color);
                }
                else if (!cursor_lb_was_pressed()) {
                  for (int i = 1; i < num_ies; i++) {
                    if (is_hovered(drawing_ies[i])) {
                      drawing_ies[i].mouse_event_handler(drawing_ies[i].color);
                      break;
                    }
                  }
                }

              if (!cursor_lb_was_pressed())
                cursor_set_lb(true);
              }
              else {
                cursor_set_lb(false);
              }
            }
          }

          if (msg.m_notify.interrupts & BIT(keyboard_bit)) {
            kbc_ih();
      
            if (get_scancode_size() == 0) { 
              mark_scancode_processed();
              continue;
            }

            if (keyboard_ready()) {
              if (scancodes[0] == ESC_KEY_BREAK) { // check early for exit 
                run = false;
                free(scancodes);        
              }

              mark_scancode_processed();

              if (get_scancode_type() == KBC_SCANCODE_BREAK) continue;

              process_scancode(scancodes, get_scancode_size(), get_scancode_type());
            }
          }
      }
    }
  }
  /* unsubscribe interrupts */

  timer_unsubscribe_int();
  kbc_unsubscribe_int();
  mouse_unsubscribe_int();

  /* disable data reporting */
  
  reset_kbc();

  /* exit graphics mode */

  vg_exit();

  return EXIT_SUCCESS;
}
