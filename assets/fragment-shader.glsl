#version 410 core

out vec4 outColour;

void main() {
    outColour = vec4(max(gl_FragCoord.z, 0) * 0.5f, 0.0f, 1.0f, 1.0f);
}