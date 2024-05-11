#include "../include/entity.h"

// todo: add null check and errors
point_t entity_tlp (entity_t * p_entity)
{
    return (p_entity->pos);
}

point_t entity_brp (entity_t * p_entity)
{
    return (
        (point_t) { p_entity->pos.x + (p_entity->size_x * p_entity->icon_size),
                    p_entity->pos.y + p_entity->size_y });
}
