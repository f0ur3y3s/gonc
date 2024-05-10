#ifndef KEYBD_H
#define KEYBD_H

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define CTRL_KEY(k) ((k) & 0x1f)

typedef enum key_constants_t
{
    KEY_UP    = 'w',
    KEY_DOWN  = 's',
    KEY_LEFT  = 'j',
    KEY_RIGHT = 'l',
    ESC_SEQ   = '\033',
} key_constants_t;

char keybd_read (void);

#endif