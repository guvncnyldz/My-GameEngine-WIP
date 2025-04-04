#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

#include <iostream>

class VBO {
public:
    VBO(const float* vertices, size_t size);
    ~VBO();

    void bind() const;
    void unbind() const;

private:
    unsigned int ID;
};

#endif
