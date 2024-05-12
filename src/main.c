#include "../include/main.h"

entity_t left_player  = { 0 };
entity_t right_player = { 0 };

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
        case PRIMARY_KEY_UP:
            // these cases should be handled by the `game` which contains the
            // screen sizes and entity size
            if (left_player.prev_pos.y > 0)
            {
                left_player.pos.y -= 1;
            }
            status = 0;
            break;
        case PRIMARY_KEY_DOWN:
            if (left_player.prev_pos.y + left_player.size_y < screen_height())
            {
                left_player.pos.y += 1;
            }
            status = 0;

            break;
        case PRIMARY_KEY_LEFT:
            if (left_player.prev_pos.x > 0)
            {
                left_player.pos.x -= left_player.icon_size;
            }
            status = 0;
            break;
        case PRIMARY_KEY_RIGHT:
            if (left_player.prev_pos.x
                    + (left_player.size_x * left_player.icon_size)
                < screen_width())
            {
                left_player.pos.x += left_player.icon_size;
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

    left_player.size_x    = 3;
    left_player.size_y    = 2;
    left_player.icon_size = 2;
    left_player.icon      = "  []  [][][]";
    left_player.pos = (point_t) { 0, (height / 2) - (left_player.size_y / 2) };
    left_player.prev_pos = left_player.pos;

    for (int y = 0; y < left_player.size_y; y++)
    {
        for (int x = 0; x < left_player.size_x * left_player.icon_size; x++)
        {
            screen_modify(
                (point_t) { x + left_player.pos.x, y + left_player.pos.y },
                left_player
                    .icon[(y * left_player.size_x * left_player.icon_size)
                          + x]);
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

        clog(L_DEBUG,
             "Position: (%d, %d)",
             left_player.pos.x,
             left_player.pos.y);
        clog(L_DEBUG,
             "Cutting buffer from (%d, %d) to (%d, %d)",
             left_player.prev_pos.x,
             left_player.prev_pos.y,
             left_player.prev_pos.x
                 + left_player.size_x * left_player.icon_size,
             left_player.prev_pos.y + left_player.size_y);

        screen_buffer_cut(
            (point_t) { left_player.prev_pos.x, left_player.prev_pos.y },
            (point_t) { left_player.prev_pos.x
                            + left_player.size_x * left_player.icon_size,
                        left_player.prev_pos.y + left_player.size_y });

        for (int y = 0; y < left_player.size_y; y++)
        {
            for (int x = 0; x < left_player.size_x * left_player.icon_size; x++)
            {
                screen_modify(
                    (point_t) { x + left_player.pos.x, y + left_player.pos.y },
                    left_player
                        .icon[(y * left_player.size_x * left_player.icon_size)
                              + x]);
            }
        }

        left_player.prev_pos = left_player.pos;
        screen_display();
    }

    screen_destroy();
    return 0;
}
