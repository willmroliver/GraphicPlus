#ifndef INCLUDE_BUFFER_HH
#define INCLUDE_BUFFER_HH

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>

class Buffer {
    private:
        GLuint id = 0;
        GLuint index;
        GLenum type;
        GLint size;
        std::vector<float> data;
        GLboolean normalized;
        GLsizei stride;

    public:
        Buffer() = default;
        Buffer(GLuint index, GLenum type, std::vector<float> data);
        Buffer(GLuint index, GLenum type, std::vector<float> data, GLint size, GLboolean normalized, GLsizei stride);
        Buffer(const Buffer& buffer) = delete;
        Buffer(Buffer&& buffer);
        ~Buffer();

        Buffer& operator=(const Buffer& buffer) = delete;
        Buffer& operator=(Buffer&& buffer);
        operator GLuint();

        void prepare();
        void bind();
        void unbind();
        void buffer_data(GLenum usage=GL_STATIC_DRAW);
        void vertex_attrib_pointer();
        void enable_vertex_attrib_array();
        void disable_vertex_attrib_array();
        void draw_arrays(GLenum mode=GL_TRIANGLES, GLsizei count=0);
};

#endif