#version 410 core
out vec4 FragColor;

void main() {
    float lerpValue = gl_FragCoord.x / 800.0f;

    FragColor = mix(
        vec4(1.0f, 0.1f, 0.2f, 1.0f),
        vec4(1.0f, 1.0f, 1.0f, 1.0f),
        lerpValue
    );
}
