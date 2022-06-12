#ifndef CANVAS_H
#define CANVAS_H

#include <lcom/lcf.h>

#include "pixel_buffer.h"
#include "../devices/video/video_gr.h"
#include "../devices/video/graphics.h"
#include "../utils/color.h"
#include "../devices/kbc/mouse.h"
#include "cursor.h"

#define CANVAS_MARGIN 60 /**< @brief */
#define CANVAS_WIDTH (H_RES - CANVAS_MARGIN * 2) /**< @brief */
#define CANVAS_HEIGHT (708) /**< @brief */

#define CANVAS_TOP_VISIBLE_LIMIT CANVAS_MARGIN /**< @brief */ 
#define CANVAS_BOTTOM_VISIBLE_LIMIT (CANVAS_MARGIN + CANVAS_HEIGHT) /**< @brief */
#define CANVAS_LEFT_VISIBLE_LIMIT CANVAS_MARGIN /**< @brief */
#define CANVAS_RIGHT_VISIBLE_LIMIT (H_RES - CANVAS_MARGIN) /**< @brief */

#define CANVAS_BYPP 1 /**< @brief */


/**
 * @brief Loads canvas information and allocates the necessary memory
 * 
 */
void (canvas_load)(); 


/**
 * @brief Returns the canvas buffer
 * 
 * @return canvas_buffer
 */
pixel_buffer const * (get_canvas_buffer)();


/**
 * @brief Draws the canvas to the back buffer
 * 
 */
void (canvas_draw)(); 


/**
 * @brief Fills an area with the given color
 * @param color color to fill the area with
 * 
 */
void (canvas_fill)(uint8_t color); 


/**
 * @brief Fills the canvas with a white color
 * 
 */
void (canvas_clear)(); 


/**
 * @brief Handles mouse events that happen within the canvas section of the screen
 * @param _ unused
 * 
 */
void (canvas_mouse_handler)(uint8_t _);


/**
 * @brief Draws a circle on screen at the given cursor position
 * 
 * @return 0 if success, 1 otherwise
 */
int (canvas_draw_pencil_circle)();


/**
 * @brief Draws a square on screen at the given cursor position
 * 
 * @return 0 if success, 1 otherwise
 */
int (canvas_draw_pencil_square)();


/**
 * @brief Handles the drawing of straight lines made by clicking on an initial and final positions
 * 
 */
void (canvas_handle_line)();


/**
 * @brief Handles the filling of an area with the cursor color
 * 
 */
void (canvas_handle_bucket)();


/**
 * @brief Recursive function to fill an area with a color
 * 
 */
void (canvas_flood_fill)(position curr_pos, uint8_t color_to_replace, uint8_t color_to_replace_with);

void (canvas_handle_text)();

/**
 * @brief Frees the memory allocated to the canvas
 * 
 */
void (canvas_exit)();


#endif
