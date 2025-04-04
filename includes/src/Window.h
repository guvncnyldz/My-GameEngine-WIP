#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    int init();
    void processInput();
    void swapBuffers();
    void pollEvents();
    int shouldClose();

    GLFWwindow* getWindow() const;


private:
    GLFWwindow* window;
    int width, height;
    const char* title;
};

#endif
