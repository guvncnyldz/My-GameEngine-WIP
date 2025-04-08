#ifndef DRAW_H
#define DRAW_H

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"

#include "pch.h"

class Draw {
public:
	Shader& shader;

	Draw(float* vertices, size_t verticesLength, unsigned int* indices, size_t indicesLength, Shader& shader);

	void setVertexAttribPointer(unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, unsigned int pointer) const;
	void run() const;
	void unbind() const;
	void update(float* vertices, size_t verticesSize, unsigned int* indices, size_t indicesSize) const;


private:
	VAO vao;
	VBO vbo;
	EBO ebo;
	unsigned int indicesSize;
};
#endif 


