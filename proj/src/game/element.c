#include <lcom/lcf.h>

#include "element.h"

bool (is_hovered)(interactive_element elem) {
  position mouse_position = cursor_get_pos();

  return (mouse_position.x >= elem.top_pos.x && 
          mouse_position.x < elem.top_pos.x + elem.h_len &&
          mouse_position.y >= elem.top_pos.y &&
          mouse_position.y < elem.top_pos.y + elem.v_len);
}
