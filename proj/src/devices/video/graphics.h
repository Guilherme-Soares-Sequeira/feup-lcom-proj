#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <lcom/lcf.h>

#include <math.h>

#include "../../game/pixel_buffer.h"
#include "../../utils/position.h"
#include "../../utils/const.h"

/**
 * @brief Draws a pixel on a pixel_buffer
 * @param buf buffer where the pixel is going to be drawn
 * @param pos position of the pixel on screen
 * @param color color of the pixel
 * 
 * @return 0 if successful, non-zero otherwise
 */
int (buf_draw_pixel)(pixel_buffer const * const buf, position pos, uint8_t color);


/**
 * @brief Draws a line on a pixel buffer
 * @param buf buffer where the line is going to be drawn
 * @param from_pos starting position of the line
 * @param to_pos final position of the line
 * @param color color of the line
 * 
 * @return 0 if successful, non-zero otherwise
 */
int (buf_draw_line)(pixel_buffer const * const buf, position from_pos, position to_pos, uint8_t color);


/**
 * @brief Draws a rectangle on a pixel buffer
 * @param pos upper-left corner coordinates of the rectangle on screen
 * @param width width of the rectangle
 * @param height height of the rectangle
 * @param color color of the rectangle
 * 
 * @return 0 if successful, non-zero otherwise
 */
int (buf_draw_rectangle)(pixel_buffer const * const buf, position pos, uint16_t width, uint16_t height, uint8_t color);


/**
 * @brief Draws a circle on a pixel buffer
 * @param pos coordinates of the center of the circle on screen
 * @param radius radius of the circle
 * @param color color of the circle
 * 
 * @return 0 if successful, non-zero otherwise
 */
int (buf_draw_circle)(pixel_buffer const * const buf, position pos, uint16_t radius, uint8_t color);




#endif
