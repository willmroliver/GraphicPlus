#include "element-buffer.hh"

ElementBuffer::ElementBuffer(std::vector<unsigned int> data, GLenum usage):
    data { data }
{
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), usage);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ElementBuffer::ElementBuffer(ElementBuffer&& buffer):
    id { buffer.id },
    data { buffer.data }
{
    buffer.id = 0;
}

ElementBuffer::~ElementBuffer() {
    glDeleteBuffers(1, &id);
}

ElementBuffer& ElementBuffer::operator=(ElementBuffer&& buffer) {
    id = buffer.id;
    data = buffer.data;

    buffer.id = 0;

    return *this;
}

ElementBuffer::operator GLuint() {
    return id;
}

void ElementBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}