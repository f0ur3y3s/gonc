#ifndef ENTITY_H
#define ENTITY_H

#include "point.h"
#include <stdbool.h>

typedef struct entity_t
{
    point_t pos;
    point_t prev_pos;
    point_t dir;
    char *  icon;
    int     size_y;
    int     size_x;
    int     icon_size;
    bool    is_collidable;
} entity_t;

int     entity_move (entity_t * p_entity, point_t dir);
point_t entity_tlp (entity_t * p_entity);
point_t entity_brp (entity_t * p_entity);
int     entity_step (entity_t * entity);

#endif // ENTITY_H