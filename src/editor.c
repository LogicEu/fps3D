#include <fps3D.h>

static cam3D cam;
static const float speed = 15.0f;
static int editor_mode;

void editor_init()
{
    editor_mode = 1;
    cam = cam3D_new(vec3_new(0.0, 1.0, 0.0), 45.0);
}

void editor_update(float delta_time)
{
    if (glee_key_pressed(GLFW_KEY_P)) {
        if (editor_mode) --editor_mode;
        else ++editor_mode;
    }

    if (editor_mode) {
        float delta_speed = delta_time * speed;
        vec2 mouse = runtime_mouse();
        cam3D_view(&cam, mouse);
        
        if (glee_key_down(GLFW_KEY_D)) {
            cam.position = vec3_add(cam.position, vec3_mult(cam.right, delta_speed));
        }
        if (glee_key_down(GLFW_KEY_A)) {
            cam.position = vec3_sub(cam.position, vec3_mult(cam.right, delta_speed));
        }
        if (glee_key_down(GLFW_KEY_W))  {
            cam.position = vec3_add(cam.position, vec3_mult(cam.direction, delta_speed));
        }
        if (glee_key_down(GLFW_KEY_S)) {
            cam.position = vec3_sub(cam.position, vec3_mult(cam.direction, delta_speed));
        }
        if (glee_key_down(GLFW_KEY_Z)) {
            cam.position = vec3_add(cam.position, vec3_mult(cam.up, delta_speed));
        }
        if (glee_key_down(GLFW_KEY_X)) {
            cam.position = vec3_sub(cam.position, vec3_mult(cam.up, delta_speed));
        }
    } else {
        player_move(delta_time);
    }

    render_view(&cam);
}