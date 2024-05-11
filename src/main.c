#include "../include/main.h"

entity_t player = { 0 };

int process_key ()
{
    int  status = 0;
    char c      = { 0 };
    int  nread  = keybd_read(&c);

    if ((-1 == nread) && (errno != EAGAIN))
    {
        if (EAGAIN != errno)
        {
            status = KEYBD_QUIT;
        }
        else
        {
            status = KEYBD_NO_READ;
        }
        goto EXIT;
    }

    switch (c)
    {
        case CTRL_KEY('q'):
            status = KEYBD_QUIT;
            break;
        case KEY_UP:
            if (player.prev_pos.y > 0)
            {
                player.pos.y -= 1;
            }
            status = 0;
            break;
        case KEY_DOWN:
            if (player.prev_pos.y + player.size_y < screen_height())
            {
                player.pos.y += 1;
            }
            status = 0;

            break;
        case KEY_LEFT:
            if (player.prev_pos.x > 0)
            {
                player.pos.x -= player.icon_size;
            }
            status = 0;
            break;
        case KEY_RIGHT:
            if (player.prev_pos.x + (player.size_x * player.icon_size)
                < screen_width())
            {
                player.pos.x += player.icon_size;
            }
            status = 0;
            break;
        default:
            status = KEYBD_NO_READ;
            break;
    }

EXIT:
    // keybd_clear();
    return (status);
}

int main (void)
{
    logger_init("test.log", L_DEBUG);

    int width  = 100;
    int height = 21;
    screen_init(width, height);
    // screen_clear();

    player.size_x    = 3;
    player.size_y    = 2;
    player.icon_size = 2;
    player.icon      = "  []  [][][]";
    player.pos       = (point_t) { 0, (height / 2) - (player.size_y / 2) };
    player.prev_pos  = player.pos;

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
        int keybd_status = process_key();

        if (KEYBD_NO_READ == keybd_status)
        {
            continue;
        }
        else if (KEYBD_QUIT == keybd_status)
        {
            break;
        }

        clog(L_DEBUG, "Position: (%d, %d)", player.pos.x, player.pos.y);
        clog(L_DEBUG,
             "Cutting buffer from (%d, %d) to (%d, %d)",
             player.prev_pos.x,
             player.prev_pos.y,
             player.prev_pos.x + player.size_x * player.icon_size,
             player.prev_pos.y + player.size_y);

        screen_buffer_cut(
            (point_t) { player.prev_pos.x, player.prev_pos.y },
            (point_t) { player.prev_pos.x + player.size_x * player.icon_size,
                        player.prev_pos.y + player.size_y });

        for (int y = 0; y < player.size_y; y++)
        {
            for (int x = 0; x < player.size_x * player.icon_size; x++)
            {
                screen_modify(
                    (point_t) { x + player.pos.x, y + player.pos.y },
                    player.icon[(y * player.size_x * player.icon_size) + x]);
            }
        }

        player.prev_pos = player.pos;
        screen_display();
    }

    screen_destroy();
    return 0;
}
