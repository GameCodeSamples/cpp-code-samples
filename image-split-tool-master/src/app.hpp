#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class App {

public:
    App();
    ~App();

    int init(const char* title);
    void run();

private:
    GLFWwindow *window;
};