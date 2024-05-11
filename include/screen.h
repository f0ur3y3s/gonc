#ifndef SCREEN_H
#define SCREEN_H

#include "point.h"
#include "term.h"
#include "logger.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SCREEN_EMPTY ' '

typedef enum screen_constants_t
{
    MIN_WIDTH  = 10,
    MIN_HEIGHT = 10,
} screen_constants_t;

typedef enum screen_retval_t
{
    S_ERR = -1,
    S_OK  = 0,
    S_UPDATE,
} screen_retval_t;

typedef struct screen_t
{
    char * pp_display_arr;
    char * pp_buffer_arr;
    int    rows;
    int    cols;
} screen_t;

/**
 * @brief Initialize the screen
 *
 * @param cols
 * @param rows
 * @return int
 */
int screen_init (int cols, int rows);

/**
 * @brief Destroy the screen
 *
 * @return int
 */
int screen_destroy (void);

/**
 * @brief Display the back buffer to the screen
 *
 * @return int
 */
int screen_display (void);

/**
 * @brief Modify a character in the back buffer
 *
 * @param pos
 * @param new_char
 * @return int
 */
int screen_modify (point_t pos, char new_char);

int screen_shift_h (int src_row, int dst_row);
int screen_shift_v (int src_col, int dst_col);

int screen_shift_selection (point_t top_point,
                            point_t bot_point,
                            point_t translation);

/**
 * @brief Clear the screen
 *
 * @note Calls screen_display after clearing.
 * @return int
 */
int screen_clear (void);

/**
 * @brief Get the screen height
 *
 * @return int
 */
int screen_height (void);

/**
 * @brief Get the screen width
 *
 * @return int
 */
int screen_width (void);

/**
 * @brief Cut the screen buffer
 *
 * @note Does not call screen_display.
 *
 * @param tlp Top left point to start cut
 * @param brp Bottom right point to end cut
 * @return int
 */
int screen_buffer_cut (point_t tlp, point_t brp);

/**
 * @brief Clear the screen buffer
 *
 * @return int
 */
int screen_buffer_clear (void);
// int        screen_render (void);

#endif // SCREEN_H

/*** end of file ***/