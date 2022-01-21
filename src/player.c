#include <fps3D.h>

static const float speed = 15.0f;

static cam3D cam;
static Entity player;

void player_init()
{
    uint8_t cols[] = {255, 55, 55, 255};
    bmp_t bmp = bmp_color(2, 2, 4, cols);

    model3D model = model3D_new(vmesh_shape_cube(1), texture_from_bmp(&bmp), glee_buffer_id());
    vec3 position = vec3_new(0.0, 1.0, 0.0);
    
    player = archetype_player(position, &model);
    cam = cam3D_new(position, 45.0);
    
    bmp_free(&bmp);
}

void player_move(float delta_time)
{
    float delta_speed = delta_time * speed;
    vec2 mouse = runtime_mouse();
    cam3D_view(&cam, mouse);

    vec3* position = entity_get(player, 0);
    vec3* velocity = entity_get(player, 1);

    const float gravity = 0.5;
    if (!collision_check(player)) {
        velocity->y -= gravity;
    } else {
        velocity->y = 0.0;
    }

    if (glee_key_down(GLFW_KEY_D)) {
        vec3 r = vec3_new(cam.right.x, 0.0, cam.right.z);
        *position = vec3_add(*position, vec3_mult(r, delta_speed));
    } if (glee_key_down(GLFW_KEY_A)) {
        vec3 r = vec3_new(cam.right.x, 0.0, cam.right.z);
        *position = vec3_sub(*position, vec3_mult(r, delta_speed));
    } if (glee_key_down(GLFW_KEY_W)) {
        vec3 d = vec3_new(cam.direction.x, 0.0, cam.direction.z);
        *position = vec3_add(*position, vec3_mult(d, delta_speed));
    } if (glee_key_down(GLFW_KEY_S)) {
        vec3 d = vec3_new(cam.direction.x, 0.0, cam.direction.z);
        *position = vec3_sub(*position, vec3_mult(d, delta_speed));
    } if (glee_key_pressed(GLFW_KEY_SPACE)) {
        velocity->y = 20.0;
    }

    *position = vec3_add(*position, vec3_mult(*velocity, delta_time));
    cam.position = *position;
}

void player_update(float delta_time)
{
    player_move(delta_time);
    render_view(&cam);
}