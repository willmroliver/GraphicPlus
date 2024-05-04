#version 410 core

smooth in vec4 color_out;
out vec4 outColour;

void main() {
    outColour = color_out;
}