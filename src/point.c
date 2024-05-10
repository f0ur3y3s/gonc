#include "../include/entity.h"

// todo: add null check and errors
point_t entity_tlp (entity_t entity)
{
    return (entity.pos);
}

point_t entity_brp (entity_t entity)
{
    return ((point_t) { entity.pos.x + (entity.size_x * entity.icon_size),
                        entity.pos.y + entity.size_y });
}
