#ifndef WINDOW_H
#define WINDOW_H

#include "pch.h"

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    int init();
    void processInput(int GLFWKey, int GLFWState, std::function<void()> callback);
    void processInputShift(int GLFWKey, int GLFWState, std::function<void()> callback);
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
