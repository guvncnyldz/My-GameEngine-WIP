#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window(int width, int height, const char* title)
	: width(width), height(height), title(title), window(nullptr) {
}

Window::~Window() {
	if (window) {
		glfwDestroyWindow(window);
	}
	glfwTerminate();
}



int Window::init() {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return 0;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return 0;
	}

	glfwSetWindowUserPointer(window, this);

	return 1;
}

void Window::setInputMode(const int mode, const int value) const
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::subscribeMouse(std::function<void(double posX, double posY)> callback)
{
	mouseCallback = callback;
}

void Window::processMouse()
{
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double posX, double posY)
		{
			Window* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));

			if (instance && instance->mouseCallback)
			{
				instance->mouseCallback(posX, posY);
			}
		});
}

void Window::processInput(int GLFWKey, int GLFWState, std::function<void()> callback) {

	if (glfwGetKey(window, GLFWKey) == GLFWState && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		callback();
}

void Window::processInputShift(int GLFWKey, int GLFWState, std::function<void()> callback) {

	if (glfwGetKey(window, GLFWKey) == GLFWState && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		callback();
}


void Window::swapBuffers() {
	glfwSwapBuffers(window);
}

void Window::pollEvents() {
	glfwPollEvents();
}

int Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

GLFWwindow* Window::getWindow() const {
	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
