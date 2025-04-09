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
    void processMouse();
    void swapBuffers();
    void pollEvents();
    int shouldClose();
    void setInputMode(const int mode, const int value) const;
    void subscribeMouse(std::function<void(double posX, double posY)>);

    GLFWwindow* getWindow() const;


    std::function<void(double posX, double posY)> mouseCallback;
private:
    GLFWwindow* window;
    int width, height;
    const char* title;
};

#endif
