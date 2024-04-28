#include "buffer.hh"

Buffer::Buffer(GLuint index, GLenum type, std::vector<float> data):
    index { index },
    type { type },
    size { 4 },
    data { data },
    normalized { GL_FALSE },
    stride { 0 }
{
    glGenBuffers(1, &id);
}

Buffer::Buffer(GLuint index, GLenum type, std::vector<float> data, GLint size, GLboolean normalized, GLsizei stride):
    index { index },
    type { type },
    size { size },
    data { data },
    normalized { normalized },
    stride { stride }
{
    glGenBuffers(1, &id);
}

Buffer::Buffer(Buffer&& buffer):
    id { buffer.id },
    index { buffer.index },
    type { buffer.type },
    size { buffer.size },
    data { buffer.data },
    normalized { buffer.normalized },
    stride { buffer.stride }
{
    buffer.id = 0;
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &id);
}

Buffer& Buffer::operator=(Buffer&& buffer) {
    id = buffer.id;
    index = buffer.index;
    type = buffer.type;
    size = buffer.size;
    data = buffer.data;
    normalized = buffer.normalized;
    stride = buffer.stride;

    buffer.id = 0;

    return *this;
}

Buffer::operator GLuint() {
    return id;
}

void Buffer::prepare() {
    bind();
    buffer_data();
    vertex_attrib_pointer();
    enable_vertex_attrib_array();
}

void Buffer::bind() {
    glBindBuffer(type, id);
}

void Buffer::unbind() {
    glBindBuffer(type, 0);
}

void Buffer::buffer_data(GLenum usage) {
    glBufferData(type, data.size() * sizeof(float), data.data(), usage);
}

void Buffer::vertex_attrib_pointer() {
    glVertexAttribPointer(index, size, GL_FLOAT, normalized, stride, (void*)0);
}

void Buffer::enable_vertex_attrib_array() {
    glEnableVertexAttribArray(index);
}

void Buffer::disable_vertex_attrib_array() {
    glDisableVertexAttribArray(index);
}

void Buffer::draw_arrays(GLenum mode, GLsizei count) {
    if (type == GL_ELEMENT_ARRAY_BUFFER) {
        return;
    }

    glDrawArrays(mode, 0, count ? count : data.size());
}