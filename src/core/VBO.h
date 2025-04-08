#ifndef VBO_H
#define VBO_H

#include "pch.h"

class VBO {
public:
    VBO(const float* vertices, size_t size);
    ~VBO();

    void bind() const;
    void unbind() const;
    void setData(const float* vertices, size_t size) const;

private:
    unsigned int ID;
};

#endif
