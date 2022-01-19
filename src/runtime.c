#include <fps3D.h>

static int runtime_mode;
static vec2 mouse;
static entity3D floor3d;

vec2 runtime_mouse()
{
    return mouse;
}

void runtime_init()
{
    runtime_mode = 1;
    
    uint8_t cols[] = {75, 75, 75, 255};
    bmp_t bmp = bmp_color(2, 2, 4, cols);
    floor3d.position = vec3_uni(0.0);
    floor3d.model = model3D_new(vmesh_shape_hex(vec3_new(100.0, 0.2, 100.0)), texture_from_bmp(&bmp), glee_buffer_id());
    bmp_free(&bmp);

    player_init();
    editor_init();
}

void runtime_update(float delta_time)
{
    glee_mouse_pos_3d(&mouse.x, &mouse.y);
    mouse = vec2_mult(mouse, 0.01);

    if (glee_key_pressed(GLFW_KEY_M)) {
        if (runtime_mode) --runtime_mode;
        else ++runtime_mode;
    }
    if (glee_key_pressed(GLFW_KEY_V)) {
        renderer_mode_switch();
    }

    if (runtime_mode) player_update(delta_time);
    else editor_update(delta_time);

    player_render();
    render_model(&floor3d.model, floor3d.position);
}