#include <fps3D.h>

static void vmesh_bind_any(unsigned int id, array_t* vertices, array_t* indices, obj_flag type)
{
    if (!vertices || !indices) return;
    unsigned int VBO, EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices->used * vertices->bytes, vertices->data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->used * indices->bytes, indices->data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertices->bytes, (void*)0);
    if (type == OBJ_VTN) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertices->bytes, (void*)offsetof(vertex_t, uv));
    }
    if (type != OBJ_V) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertices->bytes, (void*)offsetof(vertex_t, normal));
    }
}

void vmesh_bind(unsigned int id, vmesh_t* mesh)
{
    if (!mesh) return;
    vmesh_bind_any(id, mesh->vertices, mesh->indices, mesh->type);
}