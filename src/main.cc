#include "window.hh"
#include <algorithm>

int main() {
    Window w(800, 600, "Hello, World!");

    Window::set_key_callback(w, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            Window::close(window);
        }

        if (action != GLFW_PRESS && action != GLFW_REPEAT) {
            return;
        }

        const auto [x, y] = Window::size(window);

        switch (key) {
            case GLFW_KEY_UP:
                Window::resize(window, x, std::min(y - 10, 1000));
                break;
            case GLFW_KEY_DOWN:
                Window::resize(window, x, std::min(y + 10, 1000));
                break;
            case GLFW_KEY_LEFT:
                Window::resize(window, std::max(x - 10, 100), y);
                break;
            case GLFW_KEY_RIGHT:
                Window::resize(window, std::max(x + 10, 100), y);
                break;
            default:
                break;
        }
    });

    w.run();
    return 0;
}