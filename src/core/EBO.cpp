#include "EBO.h"

EBO::EBO(const unsigned int* indices, size_t size) {
    glGenBuffers(1, &ID);
    bind();
    setData(indices, size);
}

EBO::~EBO() {
    glDeleteBuffers(1, &ID);
}

void EBO::setData(const unsigned int* indices, size_t size) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
