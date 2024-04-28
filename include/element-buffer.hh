#ifndef INCLUDE_ELEMENT_BUFFER_HH
#define INCLUDE_ELEMENT_BUFFER_HH

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>

class ElementBuffer {
    private:
        GLuint id = 0;
        GLuint index;
        GLint size;
        std::vector<unsigned int> data;

    public:
        ElementBuffer() = default;
        ElementBuffer(GLuint index, std::vector<unsigned int> data);
        ElementBuffer(const ElementBuffer& buffer) = delete;
        ElementBuffer(ElementBuffer&& buffer);
        ~ElementBuffer();

        ElementBuffer& operator=(const ElementBuffer& buffer) = delete;
        ElementBuffer& operator=(ElementBuffer&& buffer);
        operator GLuint();

        void prepare();
        void bind();
        void unbind();
        void buffer_data(GLenum usage=GL_STATIC_DRAW);
        void draw_elements(GLenum mode=GL_TRIANGLES, GLsizei count=0, const void* indices=0);
};

#endif