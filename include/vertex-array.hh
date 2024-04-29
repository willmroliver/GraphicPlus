#ifndef INCLUDE_VERTEX_ARRAY_HH
#define INCLUDE_VERTEX_ARRAY_HH

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "buffer.hh"
#include "element-buffer.hh"

class VertexArray {
    private:
        GLuint id;

    public:
        VertexArray();
        ~VertexArray();
        operator GLuint();

        void bind();
        void unbind();
};

#endif