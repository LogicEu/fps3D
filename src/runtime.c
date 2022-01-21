#include <fps3D.h>

static int runtime_mode;
static vec2 mouse;

vec2 runtime_mouse()
{
    return mouse;
}

void runtime_init()
{
    runtime_mode = 1;

    scene_init();
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

    render_start();

    if (runtime_mode) player_update(delta_time);
    else editor_update(delta_time);
    
    render_components();
    render_finish();
    ui_render(glee_time_get(), delta_time);
}