#include "window.hh"
#include <algorithm>

int main() {
    Window w(600, 600, "Hello, World!");

    w.set_key_callback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto ww = static_cast<Window*>(glfwGetWindowUserPointer(window));
        
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            ww->close();
        }

        if (action != GLFW_PRESS && action != GLFW_REPEAT) {
            return;
        }

        const auto [x, y] = ww->size();

        switch (key) {
            case GLFW_KEY_UP:
                ww->resize(x, std::min(y - 10, 1000));
                break;
            case GLFW_KEY_DOWN:
                ww->resize(x, std::min(y + 10, 1000));
                break;
            case GLFW_KEY_LEFT:
                ww->resize(std::max(x - 10, 100), y);
                break;
            case GLFW_KEY_RIGHT:
                ww->resize(std::max(x + 10, 100), y);
                break;
            default:
                break;
        }
    });

    w.run();
    return 0;
}