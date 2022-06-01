#ifndef CURSOR_H
#define CURSOR_H

#include <lcom/lcf.h>
#include <lcom/video_gr.h>
#include <stdbool.h>

#include "../devices/video/video_gr.h"
#include "../utils/position.h"
#include "../utils/const.h"

#define SCALE 5
#define DEFAULT 5
#define THICKNESS(n) (n * SCALE + DEFAULT)


/**
 * @brief States that define what the mouse will draw and how it looks when hovering the canvas 
 * 
 */
typedef enum {
  CURSOR_DSTATE_CIRCLE,
  CURSOR_DSTATE_SQUARE,
  CURSOR_DSTATE_ARROW,
  CURSOR_DSTATE_LINE,
  CURSOR_DSTATE_BUCKET
} cursor_state_t;


/**
 * @brief States that define the thickness of the mouse
 * 
 */
typedef enum {
  CURSOR_DSTATE_THIN,
  CURSOR_DSTATE_REGULAR,
  CURSOR_DSTATE_THICK
} cursor_thickness_t;


/**
 * @brief Loads the xpm image of the cursor and sets it's initial coordinates
 * 
 */
void (cursor_load)();


/**
 * @brief Moves the cursor around by updating it's coordinates
 * @param delta_x x axis offset
 * @param delta_y y axis offset
 * 
 */
void (cursor_move)(int16_t delta_x, int16_t delta_y);


/**
 * @brief Returns the current position of the cursor
 * @return current position of the structure
 * 
 */
position (cursor_get_pos)();


/**
 * @brief Assigns a new value to the left button of the cursor
 * @param new_lb new value of the left button
 * 
 */
void (cursor_set_lb)(bool new_lb);


/**
 * @brief Get cursor state
 * 
 * @return cursor state
 */
cursor_state_t (cursor_get_state)();


/**
 * @brief Set cursor state
 * @param state state to be set
 */
void (cursor_set_state)(cursor_state_t state);


/**
 * @brief Get cursor thickness
 * 
 * @return cursor thickness
 */
cursor_thickness_t (cursor_get_thickness)();


/**
 * @brief Set cursor thickness
 * 
 * @return cursor thickness to be set
 */
void (cursor_set_thickness)(cursor_thickness_t thickness);


/**
 * @brief Draws the cursor on screen
 * 
 */
void (cursor_draw)();


/**
 * @brief Frees the memory allocated to the cursor
 * 
 */
void (cursor_clear)();


/**
 * @brief Indicates whether the left button was pressed or not
 * 
 * @return true if the left button was pressed, false otherwise
 */
bool (cursor_lb_pressed)();


#endif
