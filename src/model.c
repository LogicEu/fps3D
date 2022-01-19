#include <fps3D.h>

model3D model3D_new(vmesh_t* mesh, texture_t texture, unsigned int id)
{
    model3D model = {mesh, texture, id};
    vmesh_bind(model.id, model.mesh);
    return model;
}

void model3D_free(model3D* model)
{
    vmesh_free(model->mesh);
}