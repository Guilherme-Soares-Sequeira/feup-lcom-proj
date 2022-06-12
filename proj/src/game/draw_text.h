#ifndef DRAW_CHAT_H
#define DRAW_CHAT_H

#include "../utils/position.h"

#include "pixel_buffer.h"
#include "element.h"


/** @defgroup draw_chat draw_chat
 * 
 * Constants, structures and functions used for programming the drawing of the chat
 */

#define CHAR_SCALE 2 /**< @brief the scale in size of a character */

#define CHAT_HEIGHT (CHAR_HEIGHT * 2 * CHAR_SCALE/2) /**< @brief height of a character */
#define INPUT_CHAR_SIZE 80 /**< @brief size of an input character */

/**
 * @brief Adds a character to the current text 
 * @param c character to be added
 * 
 */
void (add_char_to_current_text)(char c);


/**
 * @brief Removes characters from the current text until it's empty
 * 
 */
void (clear_current_text)();


/**
 * @brief Returns the current text
 * 
 * @return text
 */
char* (get_current_text)();


/**
 * @brief Removes the last character to be added to the current text
 * 
 */
void (remove_char_from_current_text)();


/**@}*/

#endif
