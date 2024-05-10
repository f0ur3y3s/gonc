#include "../include/main.h"

typedef struct test_player_t
{
    point_t pos;
    int     size_y;
    int     size_x;
    int     icon_size;
    char *  icon;
} test_player_t;

test_player_t player = { 0 };

void process_key ()
{
    char c = keybd_read();

    switch (c)
    {
        case CTRL_KEY('q'):
            exit(0);
            break;
        case KEY_UP:
            player.pos.y -= 1;
            break;
        case KEY_DOWN:
            player.pos.y += 1;
            break;
        case KEY_LEFT:
            player.pos.x -= 1;
            break;
        case KEY_RIGHT:
            player.pos.x += 1;
            break;
        default:
            // fprintf(stdout, "%d ('%c')\r\n", c, c);
            break;
    }
}

void calculate_line (point_t start, point_t end)
{
    float dx       = (end.x - start.x);
    float dy       = (end.y - start.y);
    float distance = (pow(dx, 2) + pow(dy, 2));

    // float slope = ((end.y - start.y)/(end.x - start.x));

    for (float i = 1; i < distance; i++)
    {
        screen_modify(
            (point_t) { .x = start.x + (int)floor((dx * i) / distance),
                        .y = start.y + (int)floor((dy * i) / distance) },
            '.');
    }
}

point_t midpoint_line (point_t start, point_t end)
{
    float x = ((start.x + end.x) / 2);
    float y = ((start.y + end.y) / 2);
    clog(L_DEBUG, "Midpoint of line: %d,%d", (int)x, (int)y);
    return (point_t) { (int)x, (int)y };
}

void rotate_line (point_t * p_start, point_t * p_end, int deg)
{
}

int main (void)
{
    logger_init("test.log", L_DEBUG);
    int width  = 100;
    int height = 20;
    screen_init(width, height);
    screen_clear();

    point_t start = { 20, 0 };
    point_t end   = { 23, 20 };

    calculate_line(start, end);
    midpoint_line(start, end);

    rotate_line(&start, &end, 10);

    // calculate_line((point_t) { 0, 0 }, (point_t) { 20, 20 });
    // calculate_line((point_t) { 10, 2 }, (point_t) { 50, 20 });
    // calculate_line((point_t) { 2, 20 }, (point_t) { 50, 1 });

    screen_display();
    // player.pos       = (point_t) { 0, 0 };
    // player.size_x    = 2;
    // player.size_y    = 2;
    // player.icon_size = 2;
    // player.icon      = "[][][][]";
    // // [][]
    // // [][]

    // for (int y = 0; y < player.size_y; y++)
    // {
    //     for (int x = 0; x < player.size_x * player.icon_size; x++)
    //     {
    //         clog(L_DEBUG,
    //              "Position: (%d, %d), Character: %c\n",
    //              x + player.pos.x,
    //              y + player.pos.y,
    //              player.icon[(y * player.size_x) + x]);
    //         screen_modify(
    //             (point_t) { .x = x + player.pos.x, .y = y + player.pos.y
    //             }, player.icon[(y * player.size_x) + x]);
    //     }
    // }

    // screen_display();

    // for (;;)
    // {
    //     process_key();
    //     screen_clear();

    //     for (int y = 0; y < player.size_y; y++)
    //     {
    //         for (int x = 0; x < player.size_x * player.icon_size; x++)
    //         {
    //             clog(L_DEBUG,
    //                  "Position: (%d, %d), Character: %c\n",
    //                  x + player.pos.x,
    //                  y + player.pos.y,
    //                  player.icon[(y * player.size_x) + x]);
    //             screen_modify(
    //                 (point_t) { .x = x + player.pos.x, .y = y +
    //                 player.pos.y
    //                 }, player.icon[(y * player.size_x) + x]);
    //         }
    //     }
    //     screen_display();
    // }

    for (;;)
    {
        process_key();
    }

    screen_destroy();
    return 0;
}
