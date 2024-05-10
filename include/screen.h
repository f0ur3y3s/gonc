#ifndef SCREEN_H
#define SCREEN_H

#include "point.h"
#include "term.h"
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

int screen_init (int cols, int rows);
int screen_destroy (void);
int screen_display (void);
int screen_modify (point_t pos, char new_char);
int screen_shift_h (int src_row, int dst_row);
int screen_shift_v (int src_col, int dst_col);
int screen_shift_selection (point_t top_point, point_t bot_point, point_t translation);
int screen_clear (void);
// int        screen_render (void);

#endif // SCREEN_H

/*** end of file ***/