#include <fps3D.h>

static Module module;
static Component position, velocity, model, box3D;
static Archetype aPlayer, aBlock;

Entity archetype_player(vec3 pos, model3D* m)
{
    static vec3 vel = {0.0, 0.0, 0.0};
    static vec3 dim = {1.0, 1.0, 1.0};
    return archetype_entity(aPlayer, 4, &pos, &vel, m, &dim);
}

Entity archetype_block(vec3 pos, vec3 dim, model3D* m)
{
    return archetype_entity(aBlock, 3, &pos, m, &dim);
}

static void archetypesInit()
{
    aPlayer = archetype_create(4, position, velocity, model, box3D);
    aBlock = archetype_create(3, position, model, box3D);
}

static void moduleInit()
{
    module = module_create(0);
    position = component_create(sizeof(vec3));
    velocity = component_create(sizeof(vec3));
    model = component_create(sizeof(model3D));
    box3D = component_create(sizeof(vec3));
}

void ecs_init()
{
    ethnicInit();
    moduleInit();
    archetypesInit();
}