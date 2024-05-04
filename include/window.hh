#ifndef INCLUDE_WINDOW_HH
#define INCLUDE_WINDOW_HH

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>

class Window {
private:
    GLFWwindow* window;
    int width;
    int height;
    float z_min;
    float z_max;
    float scale;
    float perspective_matrix[16];

public:
    Window(int width, int height, std::string title);
    ~Window();
    operator GLFWwindow*();

    void run();
    void show();
    void hide();
    void close();
    std::pair<int, int> size();
    std::pair<int, int> position();
    void move(int x, int y);
    void resize(int width, int height);
    void set_title(std::string title);
    void set_key_callback(GLFWkeyfun);
};
#endif