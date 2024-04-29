#include "window.hh"
#include "programme.hh"
#include "util.hh"
#include "vertex-array.hh"
#include <cmath>
#include <functional>

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
    Programme p {
        "assets/vertex-shader.glsl",
        "assets/fragment-shader.glsl"
    };

    std::vector<float> vertices {
        // face 1
        0.5f, 0.5f, 0.0f, 1.0f,     // 0 front top right
        0.5f, -0.5f, 0.0f, 1.0f,    // 1 front bottom right
        -0.5, -0.5f, 0.0f, 1.0f,    // 2 front bottom left
        -0.5f, 0.5f, 0.0f, 1.0f,    // 3 front top left
        0.5f, 0.5f, 0.5f, 1.0f,     // 4 back top right
        0.5f, -0.5f, 0.5f, 1.0f,    // 5 back bottom right
        -0.5, 0.5, 0.5f, 1.0f,      // 6 back top left
        -0.5f, -0.5f, 0.5f, 1.0f,   // 7 back bottom left
    };

    for (unsigned long i = 0; i < vertices.size(); i += 4) {
        float x = vertices[i];
        float y = vertices[i + 1];

        float x_ = x - 0.25;
        float y_ = y - 0.25;

        vertices[i] = x_;
        vertices[i + 1] = y_;
    }

    std::vector<unsigned int> indices {
        // front face
        0, 2, 1,
        0, 3, 2,

        // rhs face
        1, 5, 4,
        1, 4, 0,

        // top face
        0, 4, 6,
        0, 6, 3,

        // bottom face
        1, 2, 7,
        1, 7, 5,

        // lhs face
        2, 3, 6,
        2, 6, 7,

        // back face
        4, 5, 6,
        6, 5, 7,
    };

    Buffer cube { GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW };
    ElementBuffer el { indices, GL_STATIC_DRAW };

    VertexArray vao;
    vao.bind();
    cube.bind();
    el.bind();
    Buffer::vertex_attrib_pointer(0, 4, GL_FALSE, 0);
    Buffer::enable_vertex_attrib_array(0);

    // set wireframe mode
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // enable face culling
    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(p);
        vao.bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

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