#ifndef KEYBD_H
#define KEYBD_H

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"

#define CTRL_KEY(k) ((k) & 0x1f)

typedef enum key_constants_t
{
    PRIMARY_KEY_UP    = 'w',
    PRIMARY_KEY_DOWN  = 's',
    PRIMARY_KEY_LEFT  = 'a',
    PRIMARY_KEY_RIGHT = 'd',
    SECONDARY_KEY_UP   = 'i',
    SECONDARY_KEY_DOWN = 'k',
    SECONDARY_KEY_LEFT = 'j',
    SECONDARY_KEY_RIGHT = 'l',
} key_constants_t;

typedef enum keybd_status_t
{
    K_CRIT = -2,
    K_OK   = 0,
} keybd_status_t;

typedef enum keybd_read_t
{
    KEYBD_NO_READ = -1,
    KEYBD_QUIT    = 500,
} keybd_read_t;

int  keybd_read (char * c);
void keybd_clear (void);

#endif