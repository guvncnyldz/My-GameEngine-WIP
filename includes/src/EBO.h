#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

#include <iostream>

class EBO {
public:
    EBO(const unsigned int* indices, size_t size);
    ~EBO();

    void bind() const;
    void unbind() const;

private:
    unsigned int ID;
};

#endif
