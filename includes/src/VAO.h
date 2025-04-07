#ifndef VAO_H
#define VAO_H

#include <pch.h>

class VAO {
public:
    VAO();
    ~VAO();

    void bind() const;
    void unbind() const;

    void setVertexAttribPointer(unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) const;

private:
    unsigned int ID;
};

#endif