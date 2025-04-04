#ifndef DRAW_H
#define DRAW_H

#include <src/VAO.h>
#include <src/VBO.h>
#include <src/EBO.h>
#include <src/Shader.h>

class Draw {
public:
	Draw(float* vertices, size_t verticesLength, unsigned int* indices, size_t indicesLength, Shader& shader);

	void setVertexAttribPointer(unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, unsigned int pointer) const;
	void run() const;
	void unbind();

private:
	VAO vao;
	VBO vbo;
	EBO ebo;
	Shader& shader;
	unsigned int indicesSize;
};
#endif 


