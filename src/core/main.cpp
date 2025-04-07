#include <glad.h>
#include <glfw3.h>

#include <Draw.h>
#include <Shader.h>
#include <Window.h>
#include <Logger.h>

float vertices[] = {
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

unsigned int indices[] = {
	0, 1, 2,
};

int main()
{
	Window window(800, 800, "My-GameEngine");

	if (!window.init())
		return -1;

	Shader shaderProgram("shaders/default/default_vertex.glsl", "shaders/default/default_fragment.glsl");
	Draw draw(vertices, 18, indices, 3, shaderProgram);
	shaderProgram.setFloat("time", 0.5f);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	draw.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	draw.setVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 3 * sizeof(float));
	draw.unbind();

	while (!window.shouldClose())
	{
		window.pollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window.processInput(GLFW_KEY_A, GLFW_PRESS, [&draw]() {
			vertices[0] = 1;
			vertices[1] = -1;
			vertices[6] = -1;
			vertices[7] = -1;
			vertices[13] = 1;

			draw.update(vertices, 18, indices, 3);
			});

		window.processInput(GLFW_KEY_S, GLFW_PRESS, [&draw]() {
			vertices[0] = 0.1;
			vertices[1] = -0.1;
			vertices[6] = -0.1;
			vertices[7] = -0.1;
			vertices[13] = 0.1;

			draw.update(vertices, 18, indices, 3);
			});

		window.processInput(GLFW_KEY_D, GLFW_PRESS, [&draw]() {
			vertices[0] = 0.05;
			vertices[1] = -0.05;
			vertices[6] = -0.05;
			vertices[7] = -0.05;
			vertices[13] = 0.05;

			draw.update(vertices, 18, indices, 3);
			});

		draw.run();
		window.swapBuffers();

		std::cout << vertices[0] << std::endl;
	}

	return 0;
}
