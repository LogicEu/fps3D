#include <fps3D.h>

const float mouse_speed = 0.005f;
const float speed = 15.0f;

void game_init()
{
    glee_init();
    glee_window_create("fps3D", 800, 600, 0, 0);
    glee_set_3d_mode();

    renderer_init();
}

void game_run()
{
    int game_mode = 1;

    uint8_t cols[] = {1.0, 1.0, 1.0, 1.0};
    bmp_t bmp = bmp_color(2, 2, 4, &cols);
    model3D model = model3D_new(vmesh_shape_hex(vec3_new(10.0, 0.2, 10.0)), texture_from_bmp(&bmp), glee_buffer_id());
    bmp_free(&bmp);

    vec3 position = {0.0, 1.0, 0.0}, velocity = {0.0, 0.0, 0.0};
    cam3D cam = cam3D_new(position, 45.0);
    vec2 mouse;

    float last_time = glee_time_get();
    while(glee_window_is_open()) {
        glee_screen_clear();

        float delta_time = glee_time_delta(&last_time);
        float delta_speed = delta_time * speed;

        glee_mouse_pos_3d(&mouse.x, &mouse.y);
        mouse = vec2_mult(mouse, 0.01);

        if (glee_key_pressed(GLFW_KEY_ESCAPE)) break;
        if (glee_key_pressed(GLFW_KEY_V)) {
            renderer_mode_switch();
        }
        if (glee_key_pressed(GLFW_KEY_M)) {
            if (game_mode) --game_mode;
            else ++game_mode;
        }

        if (!game_mode) {
            if (glee_key_down(GLFW_KEY_D)) 
                position = vec3_add(position, vec3_mult(cam.right, delta_speed));
            if (glee_key_down(GLFW_KEY_A)) 
                position = vec3_sub(position, vec3_mult(cam.right, delta_speed));
            if (glee_key_down(GLFW_KEY_W)) 
                position = vec3_add(position, vec3_mult(cam.direction, delta_speed));
            if (glee_key_down(GLFW_KEY_S)) 
                position = vec3_sub(position, vec3_mult(cam.direction, delta_speed));
            if (glee_key_down(GLFW_KEY_Z)) 
                position = vec3_add(position, vec3_mult(cam.up, delta_speed));
            if (glee_key_down(GLFW_KEY_X)) 
                position = vec3_sub(position, vec3_mult(cam.up, delta_speed));
            if (glee_key_down(GLFW_KEY_UP)) position.z += delta_speed;
            if (glee_key_down(GLFW_KEY_DOWN)) position.z -= delta_speed;
            if (glee_key_down(GLFW_KEY_RIGHT)) position.x += delta_speed;
            if (glee_key_down(GLFW_KEY_LEFT)) position.x -= delta_speed;
            velocity = vec3_uni(0.0);
            cam.position = position;
        } else {

            const float gravity = 0.5;
            if (position.y > 0.4) {
                velocity.y -= gravity;
            }
            else {
                position.y = 0.39;
                velocity.y = 0.0;
            }

            if (glee_key_down(GLFW_KEY_D)) {
                vec3 r = vec3_new(cam.right.x, 0.0, cam.right.z);
                position = vec3_add(position, vec3_mult(r, delta_speed));
            } if (glee_key_down(GLFW_KEY_A)) {
                vec3 r = vec3_new(cam.right.x, 0.0, cam.right.z);
                position = vec3_sub(position, vec3_mult(r, delta_speed));
            } if (glee_key_down(GLFW_KEY_W)) {
                vec3 d = vec3_new(cam.direction.x, 0.0, cam.direction.z);
                position = vec3_add(position, vec3_mult(d, delta_speed));
            } if (glee_key_down(GLFW_KEY_S)) {
                vec3 d = vec3_new(cam.direction.x, 0.0, cam.direction.z);
                position = vec3_sub(position, vec3_mult(d, delta_speed));
            } if (glee_key_pressed(GLFW_KEY_SPACE)) {
                velocity.y = 20.0;
            }

            position = vec3_add(position, vec3_mult(velocity, delta_time));
            cam.position = position;
        }
        
        cam3D_view(&cam, mouse);
        render_view(&cam);
        render_model(&model, vec3_uni(0.0));

        glee_screen_refresh();
    } 
}

void game_quit()
{
    glee_deinit();
    exit(EXIT_SUCCESS);
}

int main()
{
    game_init();
    game_run();
    game_quit();
    return EXIT_SUCCESS;
}