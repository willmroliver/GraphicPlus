#include "window.hh"
#include "programme.hh"
#include "util.hh"
#include "vertex-array.hh"

Window::Window(int width, int height, std::string title) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif


    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
        glViewport(0, 0, width, height);
    });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }
}

Window::~Window() {
    glfwTerminate();
}

Window::operator GLFWwindow*() {
    return window;
}

void Window::run() {
    Programme p { "assets/vertex-shader.glsl", "assets/fragment-shader.glsl" };

    std::vector<float> triangle0 {
        -0.9f,  0.1f, 0.0f,  // left 
        -0.1f,  0.1f, 0.0f,  // right
        -0.5f, 0.9f, 0.0f,  // top 
    };

    std::vector<float> triangle1 {
        0.1f, 0.1f, 0.0f,  // left
        0.9f, 0.1f, 0.0f,  // right
        0.5f, 0.9f, 0.0f,   // top 
    };

    std::vector<float> square {
        0.5f, -0.1f, 0.0f,  // top right
        0.5f, -0.9f, 0.0f,  // bottom right
        -0.5f, -0.9f, 0.0f,  // bottom left
        -0.5f, -0.1f, 0.0f,   // top left
    };
    
    std::vector<unsigned int> indices {
        0, 1, 3,
        1, 2, 3,
    };

    VertexArray triangle0_vao {
        { 0, GL_ARRAY_BUFFER, triangle0, 3, GL_FALSE, 0 }
    };

    VertexArray triangle1_vao {
        { 0, GL_ARRAY_BUFFER, triangle1, 3, GL_FALSE, 0 }
    };

    VertexArray square_vao { 
        { 0, GL_ARRAY_BUFFER, square, 3, GL_FALSE, 0 }, 
        { 0, indices }
    };

    triangle0_vao.prepare();
    triangle1_vao.prepare();
    square_vao.prepare();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.05f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(p);

        triangle0_vao.draw(GL_TRIANGLES);
        triangle1_vao.draw(GL_TRIANGLES);
        square_vao.draw(GL_TRIANGLES);
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::show(GLFWwindow* window) {
    glfwShowWindow(window);
}

void Window::hide(GLFWwindow* window) {
    glfwHideWindow(window);
}

void Window::close(GLFWwindow* window) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

std::pair<int, int> Window::size(GLFWwindow* window) {
    int x, y;
    glfwGetWindowSize(window, &x, &y);
    return { x, y };
}

std::pair<int, int> Window::position(GLFWwindow* window) {
    int x, y;
    glfwGetWindowPos(window, &x, &y);
    return { x, y };
}

void Window::move(GLFWwindow* window, int x, int y) {
    glfwSetWindowPos(window, x, y);
}

void Window::resize(GLFWwindow* window, int width, int height) {
    glfwSetWindowSize(window, width, height);
}

void Window::set_title(GLFWwindow* window, std::string title) {
    glfwSetWindowTitle(window, title.c_str());
}

void Window::set_key_callback(GLFWwindow* window, GLFWkeyfun cb) {
    glfwSetKeyCallback(window, cb);
}