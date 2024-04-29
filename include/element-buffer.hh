#ifndef INCLUDE_ELEMENT_BUFFER_HH
#define INCLUDE_ELEMENT_BUFFER_HH

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>

class ElementBuffer {
    private:
        GLuint id = 0;
        GLint size;
        std::vector<unsigned int> data;

    public:
        ElementBuffer() = default;
        ElementBuffer(std::vector<unsigned int> data, GLenum usage=GL_STATIC_DRAW);
        ElementBuffer(const ElementBuffer& buffer) = delete;
        ElementBuffer(ElementBuffer&& buffer);
        ~ElementBuffer();

        void bind();
        void unbind();

        ElementBuffer& operator=(const ElementBuffer& buffer) = delete;
        ElementBuffer& operator=(ElementBuffer&& buffer);
        operator GLuint();
};

#endif