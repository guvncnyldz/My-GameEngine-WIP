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
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

float lastX = 400, lastY = 300;
float yaw = -90, pitch = 0;
bool firstMouse = true;
float fov = 45;
void mouse_callback(double xpos, double ypos);

int main()
{
	int height = 1080;
	int width = 1080;
	//These are just experiments. Renderers, game objects, classes, etc., will come soon.


	Window window(width, height, "My-GameEngine");

	if (!window.init())
		return -1;

	glEnable(GL_DEPTH_TEST);
	window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window.getWindow(), scroll_callback);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	Shader shaderProgram("shaders/default/default_vertex.glsl", "shaders/default/default_fragment.glsl");

	Draw childRenderer(vertices, sizeof(vertices), indices, sizeof(indices), shaderProgram);

	childRenderer.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	childRenderer.setVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 3 * sizeof(float));
	//childRenderer.setVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 6 * sizeof(float));

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

	parentRenderer.setVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	parentRenderer.setVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 3 * sizeof(float));
	//parentRenderer.setVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 6 * sizeof(float));

	int texture3 = CreateTexture(GL_TEXTURE0, GL_RGBA, "assets/textures/awesomeface.png");

	parentRenderer.shader.setInt("texture1", 0);

	parentRenderer.unbind();

	glm::mat4 trans2 = glm::mat4(1.0f);
	glm::mat4 rotate2 = glm::mat4(1.0f);
	glm::mat4 position2 = glm::mat4(1.0f);
	glm::mat4 scale2 = glm::mat4(1.0f);
	position2 = glm::translate(position2, glm::vec3(2, 0, 0));

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


	while (!window.shouldClose())
	{
		window.pollEvents();
		glm::mat4 proj = glm::perspective(glm::radians(fov), (float)height / (float)width, 0.1f, 100.0f);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		float cameraSpeed = 2.5f * deltaTime;
		window.processInput(GLFW_KEY_LEFT_CONTROL, GLFW_PRESS, [&cameraSpeed, deltaTime]() {
			cameraSpeed = 5 * deltaTime;
			});
		window.processInput(GLFW_KEY_LEFT_CONTROL, GLFW_RELEASE, [&cameraSpeed, deltaTime]() {
			cameraSpeed = 2.5f * deltaTime;
			});

		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		glm::mat4 view;

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		window.subscribeMouse(mouse_callback);
		window.processMouse();

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		window.processInput(GLFW_KEY_W, GLFW_PRESS, [&cameraPos, cameraSpeed, cameraFront]() {
			cameraPos += cameraSpeed * cameraFront;
			});
		window.processInput(GLFW_KEY_S, GLFW_PRESS, [&cameraPos, cameraSpeed, cameraFront]() {
			cameraPos -= cameraSpeed * cameraFront;
			});
		window.processInput(GLFW_KEY_A, GLFW_PRESS, [&cameraPos, cameraSpeed, cameraFront, cameraUp]() {
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			});
		window.processInput(GLFW_KEY_D, GLFW_PRESS, [&cameraPos, cameraSpeed, cameraFront, cameraUp]() {
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			});


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		trans1 = position1 * rotate1 * scale1;
		//trans1 =  trans2 * trans1;

		glm::mat4 mvp1 = proj * view * trans1;
		childRenderer.shader.setMat4fv("mvp", glm::value_ptr(mvp1));

		childRenderer.run();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture3);
		trans2 = position2 * rotate2 * scale2;

		glm::mat4 mvp2 = proj * view * trans2;
		parentRenderer.shader.setMat4fv("mvp", glm::value_ptr(mvp2));
		parentRenderer.run();

		window.swapBuffers();
	}

	return 0;
}

void mouse_callback(double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

}

int CreateTexture(const int GLTexture, const int format, const char* location)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GLTexture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 90.0f)
		fov = 90.0f;

	std::cout << fov << std::endl;
}