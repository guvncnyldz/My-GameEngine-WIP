#ifndef EBO_H
#define EBO_H

#include "pch.h"

class EBO {
public:
    EBO(const unsigned int* indices, size_t size);
    ~EBO();

    void bind() const;
    void unbind() const;
    void setData(const unsigned int* indices, size_t size) const;

private:
    unsigned int ID;
};

#endif
