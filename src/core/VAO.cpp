#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
    bind();
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &ID);
}

void VAO::bind() const {
    glBindVertexArray(ID); 
}

void VAO::unbind() const {
    glBindVertexArray(0);
}

void VAO::setVertexAttribPointer(unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) const {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}
