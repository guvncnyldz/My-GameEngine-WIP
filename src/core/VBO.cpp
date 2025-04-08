#include "VBO.h"

VBO::VBO(const float* vertices, size_t size) {
    glGenBuffers(1, &ID);
    bind();
    setData(vertices, size);
}

VBO::~VBO() {
    glDeleteBuffers(1, &ID);
}

void VBO::setData(const float* vertices, size_t size) const
{
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
