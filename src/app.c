#include <fps3D.h>

static void app_init()
{
    glee_init();
    glee_window_create("fps3D", 800, 600, 0, 0);

    renderer_init();
    ui_init();
    ecs_init();
    runtime_init();
}

static void app_run()
{
    float last_time = glee_time_get();
    while(glee_window_is_open()) {
        glee_screen_clear();
        if (glee_key_pressed(GLFW_KEY_ESCAPE)) break;
        runtime_update(glee_time_delta(&last_time));
        glee_screen_refresh();
    } 
}

static void app_quit()
{
    glee_deinit();
    ethnicExit();
    exit(EXIT_SUCCESS);
}

int main()
{
    app_init();
    app_run();
    app_quit();
    return EXIT_SUCCESS;
}