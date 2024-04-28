#include "element-buffer.hh"

ElementBuffer::ElementBuffer(GLuint index, std::vector<unsigned int> data):
    index { index },
    data { data }
{
    glGenBuffers(1, &id);
}

ElementBuffer::ElementBuffer(ElementBuffer&& buffer):
    id { buffer.id },
    index { buffer.index },
    data { buffer.data }
{
    buffer.id = 0;
}

ElementBuffer::~ElementBuffer() {
    glDeleteBuffers(1, &id);
}

ElementBuffer& ElementBuffer::operator=(ElementBuffer&& buffer) {
    id = buffer.id;
    index = buffer.index;
    data = buffer.data;

    buffer.id = 0;

    return *this;
}

ElementBuffer::operator GLuint() {
    return id;
}

void ElementBuffer::prepare() {
    bind();
    buffer_data();
}

void ElementBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBuffer::buffer_data(GLenum usage) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), usage);
}

void ElementBuffer::draw_elements(GLenum mode, GLsizei count, const void* indices) {
    glDrawElements(mode, count ? count : data.size(), GL_UNSIGNED_INT, indices);
}