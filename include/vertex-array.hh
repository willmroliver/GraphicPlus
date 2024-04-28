#ifndef INCLUDE_VERTEX_ARRAY_HH
#define INCLUDE_VERTEX_ARRAY_HH

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "buffer.hh"
#include "element-buffer.hh"

class VertexArray {
    private:
        GLuint id;
        Buffer buffer;
        ElementBuffer indices;
        bool has_indices;

    public:
        VertexArray();
        VertexArray(Buffer&& buffer);
        VertexArray(Buffer&& buffer, ElementBuffer&& indices);
        ~VertexArray();
        operator GLuint();

        void prepare();
        void bind();
        void unbind();
        void draw(GLenum mode=GL_TRIANGLES);

        void set_buffer(GLuint index, std::vector<float> data);
        void set_buffer(Buffer&& buffer);
        void set_indices(GLuint index, std::vector<unsigned int> data);
        void set_indices(ElementBuffer&& indices);
};

#endif