#ifndef FPS3D_H
#define FPS3D_H

#ifdef __cplusplus
extern "C" {
#endif

/**********
 * FPS 3D
 *********/

#include <gleex.h>
#include <mass.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct model3D {
    vmesh_t* mesh;
    texture_t texture;
    unsigned int id;
} model3D;
 
typedef struct cam3D {
    vec3 position;
    vec3 direction;
    vec3 right;
    vec3 up;
    mat4 projection;
    mat4 view;
} cam3D;

model3D model3D_new(vmesh_t* mesh, texture_t texture, unsigned int id);
void model3D_free(model3D* model);

cam3D cam3D_new(vec3 position, float fov);
void cam3D_view(cam3D* cam, vec2 dir);

void vmesh_bind(unsigned int id, vmesh_t* mesh);

void renderer_init();
void render_view(cam3D* cam);
void render_model(model3D* model, vec3 position);
void renderer_mode_switch();

#ifdef __cplusplus
}
#endif
#endif