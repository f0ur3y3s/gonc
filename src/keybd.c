#include "../include/keybd.h"

int keybd_read (char * c)
{
    int nread = read(STDIN_FILENO, c, 1);

    if ((-1 == nread) && (EAGAIN != errno))
    {
        clog(L_CRIT, "Read failed, nread: %s", strerror(errno));
    }

    return (nread);
}

void keybd_clear (void)
{
    int c = { 0 };

    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}