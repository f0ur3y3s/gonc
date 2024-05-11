#include "../include/screen.h"

static screen_t *   gp_screen      = NULL;
static _Atomic bool gb_is_modified = false;

int screen_init (int cols, int rows)
{
    int status = S_ERR;

    if (MIN_WIDTH > cols || MIN_HEIGHT > rows)
    {
        goto EXIT;
    }

    gp_screen = calloc(1, sizeof(screen_t));

    if (NULL == gp_screen)
    {
        goto EXIT;
    }

    gp_screen->pp_display_arr = (char *)calloc(cols * rows, sizeof(char));

    if (NULL == gp_screen->pp_display_arr)
    {
        goto CLEANUP_SCREEN;
    }

    gp_screen->pp_buffer_arr = (char *)calloc(cols * rows, sizeof(char));

    if (NULL == gp_screen->pp_buffer_arr)
    {
        goto CLEANUP_DISPLAY;
    }

    gp_screen->cols = cols;
    gp_screen->rows = rows;
    term_uncook();
    term_clear();

    for (int y = 0; y < gp_screen->rows; y++)
    {
        for (int x = 0; x < gp_screen->cols; x++)
        {
            screen_modify((point_t) { .x = x, .y = y }, '.');
            screen_display();
            usleep(500);
        }
    }

    status = S_OK;
    goto EXIT;

CLEANUP_DISPLAY:
    free(gp_screen->pp_display_arr);
CLEANUP_SCREEN:
    free(gp_screen);
    gp_screen = NULL;
EXIT:
    return (status);
}

int screen_destroy (void)
{
    int status = S_ERR;

    if (NULL == gp_screen || NULL == gp_screen->pp_display_arr
        || NULL == gp_screen->pp_buffer_arr)
    {
        goto EXIT;
    }

    term_gotoxy(gp_screen->rows, gp_screen->cols);

    free(gp_screen->pp_display_arr);
    free(gp_screen->pp_buffer_arr);
    free(gp_screen);
    term_clear();
    term_cook();

    status = S_OK;
EXIT:
    return (status);
}

int screen_display ()
{
    int status = S_ERR;

    if (NULL == gp_screen)
    {
        goto EXIT;
    }

    if (!gb_is_modified)
    {
        status = S_OK;
        goto EXIT;
    }

    for (int row = 0; row < gp_screen->rows; row++)
    {
        for (int col = 0; col < gp_screen->cols; col++)
        {
            int acc_ptr = (row * gp_screen->cols) + col;

            if (gp_screen->pp_buffer_arr[acc_ptr]
                != gp_screen->pp_display_arr[acc_ptr])
            {
                // (void)fprintf(stderr, "Updating at x,y: %d, %d\n", col, row);
                term_gotoxy(col + 1, row + 1);
                (void)fprintf(stdout, "%c", gp_screen->pp_buffer_arr[acc_ptr]);
                fflush(stdout);
            }
        }
    }

    // if needs to update, display new screen, copy display to buffer
    memcpy(gp_screen->pp_display_arr,
           gp_screen->pp_buffer_arr,
           gp_screen->cols * gp_screen->rows * sizeof(char));

    status         = S_OK;
    gb_is_modified = false;

EXIT:
    return (status);
}

int screen_modify (point_t pos, char new_char)
{
    int status = S_ERR;

    if (NULL == gp_screen)
    {
        goto EXIT;
    }

    if (gp_screen->cols < pos.x || gp_screen->rows < pos.y)
    {
        goto EXIT;
    }

    int acc_ptr = (pos.y * gp_screen->cols) + pos.x;

    if (new_char == 0x00)
    {
        new_char = SCREEN_EMPTY;
    }

    gp_screen->pp_buffer_arr[acc_ptr] = new_char;
    // (void)fprintf(stderr, "%c", gp_screen->pp_buffer_arr[acc_ptr]);
    gb_is_modified = true;

    status = S_OK;

EXIT:
    return (status);
}

int screen_shift_h (int src_row, int dst_row)
{
    int status = S_ERR;

    if (NULL == gp_screen)
    {
        goto EXIT;
    }

    if (gp_screen->rows < src_row || gp_screen->rows < dst_row)
    {
        goto EXIT;
    }

    for (int x = 0; x < gp_screen->cols; x++)
    {
        int acc_ptr = (src_row * gp_screen->cols) + x;
        screen_modify((point_t) { .x = x, .y = dst_row },
                      gp_screen->pp_buffer_arr[acc_ptr]);
        screen_modify((point_t) { .x = x, .y = src_row }, SCREEN_EMPTY);
    }

    status = screen_display();

EXIT:
    return (status);
}

int screen_shift_v (int src_col, int dst_col)
{
    int status = S_ERR;

    if (NULL == gp_screen)
    {
        goto EXIT;
    }

    if (gp_screen->cols < src_col || gp_screen->cols < dst_col)
    {
        goto EXIT;
    }

    for (int y = 0; y < gp_screen->rows; y++)
    {
        int acc_ptr = (y * gp_screen->cols) + src_col;
        screen_modify((point_t) { .x = dst_col, .y = y },
                      gp_screen->pp_buffer_arr[acc_ptr]);
        screen_modify((point_t) { .x = src_col, .y = y }, SCREEN_EMPTY);
    }

    status = screen_display();

EXIT:
    return (status);
}

int screen_clear ()
{
    int status = S_ERR;

    if (NULL == gp_screen)
    {
        goto EXIT;
    }

    for (int i = 0; i < gp_screen->cols * gp_screen->rows; i++)
    {
        gp_screen->pp_buffer_arr[i] = SCREEN_EMPTY;
    }

    gb_is_modified = true;

    status = screen_display();

EXIT:
    return (status);
}

int screen_height (void)
{
    int height = S_ERR;

    if (NULL == gp_screen)
    {
        goto EXIT;
    }

    height = gp_screen->rows;

EXIT:
    return (height);
}

int screen_width (void)
{
    int width = S_ERR;

    if (NULL == gp_screen)
    {
        goto EXIT;
    }

    width = gp_screen->cols;

EXIT:
    return (width);
}

int screen_shift_selection (point_t top_point,
                            point_t bot_point,
                            point_t translation)
{
    int status = S_ERR;

    if (NULL == gp_screen)
    {
        goto EXIT;
    }

    if (gp_screen->cols < top_point.x || gp_screen->cols < bot_point.x
        || gp_screen->rows < top_point.y || gp_screen->rows < bot_point.y)
    {
        goto EXIT;
    }

    for (int y = top_point.y; y < bot_point.y; y++)
    {
        for (int x = top_point.x; x < bot_point.x; x++)
        {
            int acc_ptr = (y * gp_screen->cols) + x;
            screen_modify(
                (point_t) { .x = x + translation.x, .y = y + translation.y },
                gp_screen->pp_buffer_arr[acc_ptr]);
            screen_modify((point_t) { .x = x, .y = y }, SCREEN_EMPTY);
        }
    }

    status = screen_display();

EXIT:
    return (status);
}

int screen_buffer_cut (point_t tlp, point_t brp)
{
    int status = S_ERR;

    // clear the buffer from top point to bottom point
    for (int y = tlp.y; y < brp.y; y++)
    {
        for (int x = tlp.x; x < brp.x; x++)
        {
            screen_modify((point_t){ .x = x, .y = y }, SCREEN_EMPTY);
        }
    }

    return (status);
}

// int screen_cut (screen_t * gp_screen, point_t start, point_t end)
// {
//     int status = S_ERR;

//     if (NULL == gp_screen)
//     {
//         goto EXIT;
//     }

// }

// int main (void)
// {
//     screen_t * gp_screen = screen_init(20, 10);
//     printf("col: %d height: %d\n", gp_screen->col, gp_screen->height);

//     for (int i = 0; i < gp_screen->col * gp_screen->height; i++)
//     {
//         if (i % gp_screen->col == 5)
//         {
//             gp_screen->pp_display_arr[i] = '|';
//         }
//         else
//         {
//             gp_screen->pp_display_arr[i] = 'c';
//         }
//     }

//     screen_display(gp_screen);
// }