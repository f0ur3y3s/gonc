#ifndef ENTITY_H
#define ENTITY_H

#include "point.h"

typedef struct entity_t
{
    point_t pos;
    point_t prev_pos;
    int     size_y;
    int     size_x;
    int     icon_size;
    char *  icon;
    point_t dir;
} entity_t;

point_t entity_tlp (entity_t * p_entity);
point_t entity_brp (entity_t * p_entity);
int     entity_step (entity_t * entity);

#endif // ENTITY_H