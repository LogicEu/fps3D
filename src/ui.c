#include <fps3D.h>

static wxTitle title;
static wxTitle time;
static wxTitle fps;

void ui_init()
{
    int w, h;
    glee_window_get_size(&w, &h);
    gluiInit(w, h, 1);
    gluiFontSet(fontLoad("assets/fonts/Pixels.ttf", 32));
    gluiFrameSet(texture_load("assets/textures/frame16.png"));
    gluiSliderSet(
        texture_load("assets/textures/slider.png"),
        texture_load("assets/textures/marker.png")
    );
    gluiSwitchSet(
        texture_load("assets/textures/switch_down.png"),
        texture_load("assets/textures/switch_up.png")
    );

    vec4 red = {1.0, 0.0, 0.0, 1.0};
    title = wxTitleCreate("FPS 3D Engine", vec3_new(32, h - 48, 2.0), red);
    time = wxTitleCreate("Time: 0.00", vec3_new(32, h - 72, 1.5), red);
    fps = wxTitleCreate("FPS: 0.0", vec3_new(32, h - 96, 1.5), red);
}

void ui_render(float t, float delta_time)
{
    float f = 60.0 / delta_time;
    sprintf(time.string, "Time: %.02f", t);

    static unsigned int counter = 1;
    if (counter % 100 == 0) sprintf(fps.string, "FPS: %.01f", f);
    counter++;
    
    wxTitleDraw(&title);
    wxTitleDraw(&time);
    wxTitleDraw(&fps);
}