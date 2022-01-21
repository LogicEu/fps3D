#include <fps3D.h>

void scene_init()
{
    uint8_t grey[] = {75, 75, 75, 255};
    uint8_t blue[] = {0, 0, 255, 255};

    bmp_t bmp_grey = bmp_color(2, 2, 4, grey);
    bmp_t bmp_blue = bmp_color(2, 2, 4, blue);
    
    vec3 dimension = vec3_new(100.0, 0.2, 100.0);
    model3D floor = model3D_new(vmesh_shape_hex(dimension), texture_from_bmp(&bmp_grey), glee_buffer_id());
    model3D cube = model3D_new(vmesh_shape_cube(1), texture_from_bmp(&bmp_blue), glee_buffer_id());
    
    archetype_block(vec3_uni(0.0), dimension, &floor);

    vec3 u = vec3_uni(1.0);
    for (int i = 0; i < 10; i++) {
        archetype_block(vec3_uni((float)i), u, &cube);
    }
    
    bmp_free(&bmp_grey);
    bmp_free(&bmp_blue);
}