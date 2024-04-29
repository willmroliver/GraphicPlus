#include "buffer.hh"

Buffer::Buffer(GLenum type):
    type { type }
{
    glGenBuffers(1, &id);
}

Buffer::Buffer(GLenum type, std::vector<float>& data, GLenum usage):
    type { type }
{
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
    glBufferData(type, data.size() * sizeof(float), data.data(), usage);
    glBindBuffer(type, 0);
}

Buffer::Buffer(Buffer&& buffer):
    id { buffer.id },
    type { buffer.type }
{
    buffer.id = 0;
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &id);
}

Buffer& Buffer::operator=(Buffer&& buffer) {
    id = buffer.id;
    type = buffer.type;

    buffer.id = 0;

    return *this;
}

Buffer::operator GLuint() {
    return id;
}

void Buffer::bind() {
    glBindBuffer(type, id);
}

void Buffer::unbind() {
    glBindBuffer(type, 0);
}

void Buffer::data(std::vector<float>& data, GLenum usage) {
    bind();
    glBufferData(type, data.size() * sizeof(float), data.data(), usage);
    unbind();
}

void Buffer::sub_data(std::vector<float>& data, int from) {
    bind();
    glBufferSubData(type, from * sizeof(float), data.size() * sizeof(float), data.data());
    unbind();
}

void Buffer::vertex_attrib_pointer(GLuint index, GLint size, GLboolean normalized, GLsizei stride, unsigned int from) {
    glVertexAttribPointer(index, size, GL_FLOAT, normalized, stride, (void*)from);
}

void Buffer::enable_vertex_attrib_array(GLuint index) {
    glEnableVertexAttribArray(index);
}

void Buffer::disable_vertex_attrib_array(GLuint index) {
    glDisableVertexAttribArray(index);
}
