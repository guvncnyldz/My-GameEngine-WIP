#include <src/Draw.h>
#include <iterator>
#include <algorithm>

Draw::Draw(float* vertices, size_t verticesSize, unsigned int* indices, size_t indicesSize, Shader& shader)
    : vao(), vbo(vertices, verticesSize * sizeof(float)), ebo(indices, indicesSize * sizeof(unsigned int)), shader(shader), indicesSize(indicesSize)
{
}


void Draw::setVertexAttribPointer(unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, unsigned int pointer) const
{
    vao.setVertexAttribPointer(index, size, type, normalized, stride, (void*)pointer);
}

void Draw::run() const
{
    shader.use();

    vao.bind();
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
    vao.unbind();
}

void Draw::unbind()
{
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}