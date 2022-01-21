#include <fps3D.h>

unsigned int lightshader, framebuffer_shader;
unsigned int draw_kind;
unsigned int quadID;

static framebuffer_t framebuffer;
static mat4 matId;
static vec3 vZero;

static void renderer_shaders_init()
{
    framebuffer = framebuffer_new();

    quadID = glee_buffer_quad_create();

    framebuffer_shader = glee_shader_load("shaders/framebufferv.frag", "shaders/framebufferf.frag");

    lightshader = glee_shader_load("shaders/lightv.frag", "shaders/light.frag");
    
    glUniform3f(glGetUniformLocation(lightshader, "global_light.direction"), -0.5f, -1.0f, -0.5f);
    glUniform3f(glGetUniformLocation(lightshader, "global_light.ambient"), 0.7f, 0.7f, 0.7f);
    glUniform3f(glGetUniformLocation(lightshader, "global_light.diffuse"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(lightshader, "global_light.specular"), 0.7f, 0.7f, 0.7f);

    glUniform3f(glGetUniformLocation(lightshader, "point_light.position"), 4.0f, 8.0f, 4.0f); 
    glUniform3f(glGetUniformLocation(lightshader, "point_light.ambient"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(lightshader, "point_light.diffuse"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(lightshader, "point_light.specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(lightshader, "point_light.constant"), .01f);
    glUniform1f(glGetUniformLocation(lightshader, "point_light.linear"), 0.01f);
    glUniform1f(glGetUniformLocation(lightshader, "point_light.quadratic"), 0.1f);
    glUniform1f(glGetUniformLocation(lightshader, "shininess"), 32.0f);
}

void renderer_mode_switch()
{
    if (draw_kind == 0x0004) draw_kind = 0x0001;
    else draw_kind = 0x0004;
}

void render_light_position(vec3 position)
{
    glUniform3f(glGetUniformLocation(lightshader, "point_light.position"), position.x, position.y, position.z);
}

void render_view(cam3D* cam)
{
    glUseProgram(lightshader);
    glUniformMatrix4fv(glGetUniformLocation(lightshader, "view"), 1, GL_FALSE, &cam->view.data[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(lightshader, "projection"), 1, GL_FALSE, &cam->projection.data[0][0]);
    glUniform3f(glGetUniformLocation(lightshader, "viewPos"), cam->position.x, cam->position.y, cam->position.z);
}

void render_model(model3D* model, vec3 position)
{
    mat4 m = mat4_translate(matId, position);

    glBindVertexArray(model->id);
    glBindTexture(GL_TEXTURE_2D, model->texture.id);
    glUniformMatrix4fv(glGetUniformLocation(lightshader, "model"), 1, GL_FALSE, &m.data[0][0]);
    glDrawElements(draw_kind, model->mesh->indices->used, GL_UNSIGNED_INT, 0);
}

void renderer_init()
{
    draw_kind = 4;
    matId = mat4_id();
    vZero = vec3_uni(0.0);

    renderer_shaders_init();
    
    int w, h;
    glee_window_get_size(&w, &h);
    glee_screen_color(0.5, 0.5, 1.0, 1.0);
}

void render_components()
{
    int size = component_entity_count(0);
    model3D* model = component_get(2);
    for (int i = 0; i < size; i++) {
        vec3 pos = *(vec3*)entity_get(entity_find(0, i), 0);
        render_model(model++, pos);
    }
}

void render_start()
{
    framebuffer_bind(framebuffer.id);
    glee_set_3d_mode();
    glee_screen_clear();
}

void render_finish()
{
    framebuffer_bind(0);

    glee_set_2d_mode();
    glUseProgram(framebuffer_shader);
    glBindVertexArray(quadID);
    glBindTexture(GL_TEXTURE_2D, framebuffer.texture.id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}