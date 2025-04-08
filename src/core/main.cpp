#include <glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Draw.h"
#include "Shader.h"
#include "Window.h"
#include "Logger.h"

#include <stb_image.h>

int CreateTexture(const int GLTexture, const int format, const char* location);

float vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main()
{
	int height = 1920;
	int width = 1080;
	//These are just experiments. Renderers, game objects, classes, etc., will come soon.
	Window window(width, height, "My-GameEngine");

	if (!window.init())
		return -1;

	Shader shaderProgram("shaders/default/default_vertex.glsl", "shaders/default/default_fragment.glsl");
	Draw childRenderer(vertices, sizeof(vertices), indices, sizeof(indices), shaderProgram);

	childRenderer.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	childRenderer.setVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 3 * sizeof(float));
	childRenderer.setVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 6 * sizeof(float));

	int texture1 = CreateTexture(GL_TEXTURE0, GL_RGB, "assets/textures/container.jpg");
	int texture2 = CreateTexture(GL_TEXTURE1, GL_RGBA, "assets/textures/awesomeface.png");

	childRenderer.shader.setInt("texture1", 0);
	childRenderer.shader.setInt("texture2", 1);

	childRenderer.unbind();

	glm::mat4 trans1 = glm::mat4(1.0f);
	glm::mat4 rotate1 = glm::mat4(1.0f);
	glm::mat4 position1 = glm::mat4(1.0f);
	glm::mat4 scale1 = glm::mat4(1.0f);

	Shader shaderProgram2("shaders/default/default_vertex.glsl", "shaders/default/default_fragment.glsl");
	Draw parentRenderer(vertices, sizeof(vertices), indices, sizeof(indices), shaderProgram2);

	parentRenderer.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	parentRenderer.setVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 3 * sizeof(float));
	parentRenderer.setVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 6 * sizeof(float));

	int texture3 = CreateTexture(GL_TEXTURE0, GL_RGBA, "assets/textures/awesomeface.png");

	parentRenderer.shader.setInt("texture1", 0);

	parentRenderer.unbind();

	glm::mat4 trans2 = glm::mat4(1.0f);
	glm::mat4 rotate2 = glm::mat4(1.0f);
	glm::mat4 position2 = glm::mat4(1.0f);
	glm::mat4 scale2 = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)height / (float)width, 0.1f, 100.0f);

	while (!window.shouldClose())
	{
		window.pollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		window.processInput(GLFW_KEY_T, GLFW_PRESS, [&view]() {
			//zoom out
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
			});
		window.processInput(GLFW_KEY_G, GLFW_PRESS, [&view]() {
			//zoom in
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, 1.0f));
			});

		window.processInput(GLFW_KEY_R, GLFW_PRESS, [&scale1]() {
			//scale up
			scale1 = glm::scale(scale1, glm::vec3(1+0.05f, 1+0.05f,0));
			});
		window.processInput(GLFW_KEY_F, GLFW_PRESS, [&scale1]() {
			//scale down
			scale1 = glm::scale(scale1, glm::vec3(1 - 0.05f, 1 - 0.05f, 0));
			});

		window.processInput(GLFW_KEY_W, GLFW_PRESS, [&position1]() {
			//move up
			position1 = glm::translate(position1, glm::vec3(0, 0.05f, 0.0f));
			});
		window.processInput(GLFW_KEY_S, GLFW_PRESS, [&position1]() {
			//move down
			position1 = glm::translate(position1, glm::vec3(0, -0.05f, 0.0f));
			});
		window.processInput(GLFW_KEY_A, GLFW_PRESS, [&position1]() {
			//move left
			position1 = glm::translate(position1, glm::vec3(-0.05f, 0, 0.0f));
			});
		window.processInput(GLFW_KEY_D, GLFW_PRESS, [&position1]() {
			//move right
			position1 = glm::translate(position1, glm::vec3(0.05f, 0, 0.0f));
			});

		window.processInput(GLFW_KEY_KP_7, GLFW_PRESS, [&rotate1]() {
			//rotate counterclockwise
			rotate1 = glm::rotate(rotate1, glm::radians(0.5f), glm::vec3(0.0f, 0, 1));
			});
		window.processInput(GLFW_KEY_KP_9, GLFW_PRESS, [&rotate1]() {
			//rotate clockwise
			rotate1 = glm::rotate(rotate1, glm::radians(-0.5f), glm::vec3(0.0f, 0, 1));
			});
		window.processInput(GLFW_KEY_KP_4, GLFW_PRESS, [&rotate1]() {
			//rotate left
			rotate1 = glm::rotate(rotate1, glm::radians(0.5f), glm::vec3(0.0f, 1, 0));
			});
		window.processInput(GLFW_KEY_KP_6, GLFW_PRESS, [&rotate1]() {
			//rotate right
			rotate1 = glm::rotate(rotate1, glm::radians(-0.5f), glm::vec3(0.0f, 1, 0));
			});
		window.processInput(GLFW_KEY_KP_8, GLFW_PRESS, [&rotate1]() {
			//rotate forward
			rotate1 = glm::rotate(rotate1, glm::radians(0.5f), glm::vec3(1.0f, 0, 0));
			});
		window.processInput(GLFW_KEY_KP_2, GLFW_PRESS, [&rotate1]() {
			//rotate backward
			rotate1 = glm::rotate(rotate1, glm::radians(-0.5f), glm::vec3(1.0f, 0, 0));
			});

		///////////////////////////////

		window.processInputShift(GLFW_KEY_R, GLFW_PRESS, [&scale2]() {
			//scale up
			scale2 = glm::scale(scale2, glm::vec3(1 + 0.05f, 1 + 0.05f, 0));
			});
		window.processInputShift(GLFW_KEY_F, GLFW_PRESS, [&scale2]() {
			//scale down
			scale2 = glm::scale(scale2, glm::vec3(1 - 0.05f, 1 - 0.05f, 0));
			});

		window.processInputShift(GLFW_KEY_W, GLFW_PRESS, [&position2]() {
			//move up
			position2 = glm::translate(position2, glm::vec3(0, 0.05f, 0.0f));
			});
		window.processInputShift(GLFW_KEY_S, GLFW_PRESS, [&position2]() {
			//move down
			position2 = glm::translate(position2, glm::vec3(0, -0.05f, 0.0f));
			});
		window.processInputShift(GLFW_KEY_A, GLFW_PRESS, [&position2]() {
			//move left
			position2 = glm::translate(position2, glm::vec3(-0.05f, 0, 0.0f));
			});
		window.processInputShift(GLFW_KEY_D, GLFW_PRESS, [&position2]() {
			//move right
			position2 = glm::translate(position2, glm::vec3(0.05f, 0, 0.0f));
			});

		window.processInputShift(GLFW_KEY_KP_7, GLFW_PRESS, [&rotate2]() {
			//rotate counterclockwise
			rotate2 = glm::rotate(rotate2, glm::radians(0.5f), glm::vec3(0.0f, 0, 1));
			});
		window.processInputShift(GLFW_KEY_KP_9, GLFW_PRESS, [&rotate2]() {
			//rotate clockwise
			rotate2 = glm::rotate(rotate2, glm::radians(-0.5f), glm::vec3(0.0f, 0, 1));
			});
		window.processInputShift(GLFW_KEY_KP_4, GLFW_PRESS, [&rotate2]() {
			//rotate left
			rotate2 = glm::rotate(rotate2, glm::radians(0.5f), glm::vec3(0.0f, 1, 0));
			});
		window.processInputShift(GLFW_KEY_KP_6, GLFW_PRESS, [&rotate2]() {
			//rotate right
			rotate2 = glm::rotate(rotate2, glm::radians(-0.5f), glm::vec3(0.0f, 1, 0));
			});
		window.processInputShift(GLFW_KEY_KP_8, GLFW_PRESS, [&rotate2]() {
			//rotate forward
			rotate2 = glm::rotate(rotate2, glm::radians(0.5f), glm::vec3(1.0f, 0, 0));
			});
		window.processInputShift(GLFW_KEY_KP_2, GLFW_PRESS, [&rotate2]() {
			//rotate backward
			rotate2 = glm::rotate(rotate2, glm::radians(-0.5f), glm::vec3(1.0f, 0, 0));
			});

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture3);
		trans2 = position2 * rotate2 * scale2;
		parentRenderer.shader.setMat4fv("model", glm::value_ptr(trans2));
		parentRenderer.shader.setMat4fv("view", glm::value_ptr(view));
		parentRenderer.shader.setMat4fv("projection", glm::value_ptr(proj));
		parentRenderer.run();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		trans1 = position1 * rotate1 * scale1;
		//trans1 =  trans2 * trans1;
		childRenderer.shader.setMat4fv("model", glm::value_ptr(trans1));
		childRenderer.shader.setMat4fv("view", glm::value_ptr(view));
		childRenderer.shader.setMat4fv("projection", glm::value_ptr(proj));
		childRenderer.run();

		window.swapBuffers();
	}

	return 0;
}

int CreateTexture(const int GLTexture, const int format, const char* location)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GLTexture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(location, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	return texture;
}