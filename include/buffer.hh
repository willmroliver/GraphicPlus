#ifndef INCLUDE_BUFFER_HH
#define INCLUDE_BUFFER_HH

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>

class Buffer {
    private:
        GLuint id = 0;
        GLenum type;

    public:
        Buffer() = default;
        Buffer(GLenum type);
        Buffer(GLenum type, std::vector<float>& data, GLenum usage=GL_STATIC_DRAW);
        Buffer(const Buffer& buffer) = delete;
        Buffer(Buffer&& buffer);
        ~Buffer();

        Buffer& operator=(const Buffer& buffer) = delete;
        Buffer& operator=(Buffer&& buffer);
        operator GLuint();
        
        void bind();
        void unbind();

        void data(std::vector<float>& data, GLenum usage=GL_STATIC_DRAW);
        void sub_data(std::vector<float>& data, int from);

        static void vertex_attrib_pointer(GLuint index, GLint size, GLboolean normalized=GL_FALSE, GLsizei stride=0, unsigned int from=0);
        static void enable_vertex_attrib_array(GLuint index);
        static void disable_vertex_attrib_array(GLuint index);
};

#endif