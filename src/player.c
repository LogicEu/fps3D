#include <fps3D.h>

static const float speed = 15.0f;

static cam3D cam;
static entity3D player;
static vec3 velocity;

void player_init()
{
    uint8_t cols[] = {255, 55, 55, 255};
    bmp_t bmp = bmp_color(2, 2, 4, cols);
    player.model = model3D_new(vmesh_shape_cube(1), texture_from_bmp(&bmp), glee_buffer_id());
    bmp_free(&bmp);

    player.position = vec3_new(0.0, 1.0, 0.0);
    cam = cam3D_new(player.position, 45.0);
    velocity = vec3_uni(0.0);
}

void player_render()
{
    render_model(&player.model, player.position);
}

void player_move(float delta_time)
{
    float delta_speed = delta_time * speed;
    vec2 mouse = runtime_mouse();
    cam3D_view(&cam, mouse);

    const float gravity = 0.5;
    if (player.position.y > PLAYER_HEIGHT) {
        velocity.y -= gravity;
    }
    else {
        player.position.y = PLAYER_HEIGHT - TINY_OFFSET;
        velocity.y = 0.0;
    }

    if (glee_key_down(GLFW_KEY_D)) {
        vec3 r = vec3_new(cam.right.x, 0.0, cam.right.z);
        player.position = vec3_add(player.position, vec3_mult(r, delta_speed));
    } if (glee_key_down(GLFW_KEY_A)) {
        vec3 r = vec3_new(cam.right.x, 0.0, cam.right.z);
        player.position = vec3_sub(player.position, vec3_mult(r, delta_speed));
    } if (glee_key_down(GLFW_KEY_W)) {
        vec3 d = vec3_new(cam.direction.x, 0.0, cam.direction.z);
        player.position = vec3_add(player.position, vec3_mult(d, delta_speed));
    } if (glee_key_down(GLFW_KEY_S)) {
        vec3 d = vec3_new(cam.direction.x, 0.0, cam.direction.z);
        player.position = vec3_sub(player.position, vec3_mult(d, delta_speed));
    } if (glee_key_pressed(GLFW_KEY_SPACE)) {
        velocity.y = 20.0;
    }

    player.position = vec3_add(player.position, vec3_mult(velocity, delta_time));
    cam.position = player.position;
}

void player_update(float delta_time)
{
    player_move(delta_time);
    render_view(&cam);
}