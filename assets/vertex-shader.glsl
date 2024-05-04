#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

smooth out vec4 color_out;

uniform vec2 offset;
uniform mat4 p_matrix;

void main() {
    vec4 camera_pos = position + vec4(offset, 0.0, 0.0);
    gl_Position = p_matrix * camera_pos;
    color_out = color;
}
