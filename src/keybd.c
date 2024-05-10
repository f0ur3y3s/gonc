#include "../include/keybd.h"

char keybd_read (void)
{
    int  nread;
    char c = { 0 };

    while (1 != (nread = read(STDIN_FILENO, &c, 1)))
    {
        if (nread == -1 && errno != EAGAIN)
        {
            exit(1);
        }
    }

    return c;
}

