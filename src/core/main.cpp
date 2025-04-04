#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <src/Draw.h>
#include <src/Shader.h>
#include <src/Window.h>

float vertices[] = {
	0.5f,  0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   -0.5f,  0.5f, 0.0f,
	0.7f,  0.6f, -0.2f,
	0.7f,  -0.4f, -0.2f,
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3,
	0, 1, 5,
	0, 4, 5
};

int main()
{
	Window window(800, 800, "My-GameEngine");

	if (!window.init())
		return -1;

	Shader shaderProgram("shaders/default/default_vertex.glsl", "shaders/default/default_fragment.glsl");

	Draw draw(vertices, 18, indices, 12, shaderProgram);
	draw.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	draw.unbind();

	while (!window.shouldClose())
	{
		window.pollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		draw.run();

		window.swapBuffers();
		window.processInput();
	}

	return 0;
}
