#include "pch.h"
#include "Draw.h"

Draw::Draw(float* vertices, size_t verticesSize, unsigned int* indices, size_t indicesSize, Shader& shader)
    : vao(), vbo(vertices, verticesSize), ebo(indices, indicesSize), shader(shader), indicesSize(indicesSize)
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
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
    vao.unbind();
}

void Draw::unbind() const
{
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}

void Draw::update(float* vertices, size_t verticesSize, unsigned int* indices, size_t indicesSize) const
{
    vbo.bind();
    vbo.setData(vertices, verticesSize * sizeof(float));

    ebo.bind();
    ebo.setData(indices, indicesSize * sizeof(float));
    unbind();
}