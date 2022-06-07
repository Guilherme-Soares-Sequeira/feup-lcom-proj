#ifndef CURSOR_H
#define CURSOR_H

#include <lcom/lcf.h>
#include <lcom/video_gr.h>
#include <stdbool.h>

#include "../devices/video/video_gr.h"
#include "../utils/position.h"
#include "../utils/const.h"
#include "../utils/color.h"

#define MIN_THICKNESS 1
#define MAX_THICKNESS 16


/**
 * @brief States that define what the mouse will draw and how it looks when hovering the canvas 
 * 
 */
typedef enum cursor_style {
  CURSOR_DSTATE_CIRCLE,
  CURSOR_DSTATE_SQUARE,
  CURSOR_DSTATE_ARROW,
  CURSOR_DSTATE_LINE,
  CURSOR_DSTATE_BUCKET
} cursor_state_style_t;


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
 * @brief Gets the current style of the cursor
 * 
 * @return cursor style
 */
cursor_state_style_t (cursor_get_style)();


/**
 * @brief Set cursor state
 * @param state state to be set
 */
void (cursor_set_style)(cursor_state_style_t style);


/**
 * @brief Get cursor thickness
 * 
 * @return cursor thickness
 */
uint8_t (cursor_get_thickness)();


/**
 * @brief Set cursor thickness
 * 
 * @return cursor thickness to be set
 */
void (cursor_set_thickness)(uint8_t thickness);

void (cursor_increase_thickness)();

void (cursor_decrease_thickness)();

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
 * @brief Assigns a new value to the left button of the cursor
 * @param new_lb new value of the left button
 * 
 */
void (cursor_set_lb)(bool lb);


/**
 * @brief Indicates whether the left button was pressed or not
 * 
 * @return true if the left button was pressed, false otherwise
 */
bool (cursor_lb_pressed)();

uint8_t (cursor_get_color)();


void (cursor_set_color_black)();

void (cursor_set_color_blue)();

void (cursor_set_color_green)();

void (cursor_set_color_red)();

void (cursor_set_color_brown)();

void (cursor_set_color_yellow)();

#endif
