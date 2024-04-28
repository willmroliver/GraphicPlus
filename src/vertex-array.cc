#include "vertex-array.hh"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

VertexArray::VertexArray(Buffer&& buffer):
    buffer { std::move(buffer) },
    has_indices { false }
{
    glGenVertexArrays(1, &id);
}

VertexArray::VertexArray(Buffer&& buffer, ElementBuffer&& indices):
    buffer { std::move(buffer) },
    indices { std::move(indices) },
    has_indices { true }
{
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

VertexArray::operator GLuint() {
    return id;
}

void VertexArray::prepare() {
    bind();
    buffer.prepare();
    if (has_indices) {
        indices.prepare();
    }
}

void VertexArray::bind() {
    glBindVertexArray(id);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::draw(GLenum mode) {
    bind();
    if (has_indices) {
        indices.draw_elements(mode);
    } else {
        buffer.draw_arrays(mode);
    }
}

void VertexArray::set_buffer(GLuint index, std::vector<float> data) {
    buffer = Buffer { index, GL_ARRAY_BUFFER, data };
}

void VertexArray::set_buffer(Buffer&& buffer) {
    this->buffer = std::move(buffer);
}

void VertexArray::set_indices(GLuint index, std::vector<unsigned int> data) {
    indices = ElementBuffer { index, data };
    has_indices = true;
}

void VertexArray::set_indices(ElementBuffer&& indices) {
    this->indices = std::move(indices);
    has_indices = true;
}