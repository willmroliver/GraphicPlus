#ifndef INCLUDE_WINDOW_HH
#define INCLUDE_WINDOW_HH

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <functional>
#include <string>

class Window {
private:
    GLFWwindow* window;

public:
    Window(int width, int height, std::string title);
    ~Window();
    operator GLFWwindow*();

    void run();
    static void show(GLFWwindow* window);
    static void hide(GLFWwindow* window);
    static void close(GLFWwindow* window);
    static std::pair<int, int> size(GLFWwindow* window);
    static std::pair<int, int> position(GLFWwindow* window);
    static void move(GLFWwindow* window, int x, int y);
    static void resize(GLFWwindow* window, int width, int height);
    static void set_title(GLFWwindow* window, std::string title);
    static void set_key_callback(GLFWwindow* window, GLFWkeyfun);
};

#endif