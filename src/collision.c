#include <fps3D.h>

bool collision_check(Entity entity)
{
    unsigned int size = component_entity_count(3);
    for (unsigned int i = 0; i < size; i++) {
        
        Entity e = entity_find(3, i);
        if (e == entity) continue;

        vec3* adim = entity_get(entity, 3);
        vec3* apos = entity_get(entity, 0);

        vec3* bdim = entity_get(e, 3);
        vec3* bpos = entity_get(e, 0);

        if (hex3D_overlap(hex3D_new(*adim, *apos), hex3D_new(*bdim, *bpos))) {
            return true;
        }
    }
    return false;
}