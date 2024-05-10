#include "../include/main.h"

entity_t player = { 0 };

int process_key ()
{
    int  status = 0;
    char c      = keybd_read();

    switch (c)
    {
        case CTRL_KEY('q'):
            status = -1;
            break;
        case KEY_UP:
            if (player.prev_pos.y > 0)
            {
                player.pos.y -= 1;
            }
            break;
        case KEY_DOWN:
            if (player.prev_pos.y + player.size_y < screen_height())
            {
                player.pos.y += 1;
            }
            break;
        case KEY_LEFT:
            if (player.prev_pos.x > 0)
            {
                player.pos.x -= player.icon_size;
            }
            break;
        case KEY_RIGHT:
            if (player.prev_pos.x + (player.size_x * player.icon_size)
                < screen_width())
            {
                player.pos.x += player.icon_size;
            }
            break;
        default:
            // fprintf(stdout, "%d ('%c')\r\n", c, c);
            break;
    }

    return (status);
}

int main (void)
{
    logger_init("test.log", L_DEBUG);

    int width  = 100;
    int height = 20;
    screen_init(width, height);
    screen_clear();

    player.pos       = (point_t) { 0, 0 };
    player.prev_pos  = (point_t) { 0, 0 };
    player.size_x    = 1;
    player.size_y    = 5;
    player.icon_size = 2;
    player.icon      = "[][][][][]";

    for (int y = 0; y < player.size_y; y++)
    {
        for (int x = 0; x < player.size_x * player.icon_size; x++)
        {
            screen_modify(
                (point_t) { x + player.pos.x, y + player.pos.y },
                player.icon[(y * player.size_x * player.icon_size) + x]);
        }
    }

    screen_display();

    for (;;)
    {
        if (0 != process_key())
        {
            break;
        }

        clog(L_DEBUG, "Position: (%d, %d)", player.pos.x, player.pos.y);
        // screen_shift_selection(entity_tlp(player),
        //                        entity_brp(player),
        //                        (point_t) { player.pos.x - player.prev_pos.x,
        //                                    player.pos.y - player.prev_pos.y
        //                                    });

        // This is bad, we want to update the screen positionally and not by
        // clearing and updating the entire back buffer and then displaying it
        screen_clear();

        for (int y = 0; y < player.size_y; y++)
        {
            for (int x = 0; x < player.size_x * player.icon_size; x++)
            {
                screen_modify(
                    (point_t) { x + player.pos.x, y + player.pos.y },
                    player.icon[(y * player.size_x * player.icon_size) + x]);
            }
        }

        // calculate spaces that player.pos now occupies

        player.prev_pos = player.pos;

        screen_display();
    }

    screen_destroy();
    return 0;
}
