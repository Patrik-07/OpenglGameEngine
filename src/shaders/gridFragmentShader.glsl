#version 330 core

in vec3 position;

out vec4 FragColor;

uniform vec3 cameraPosition;

void main() {
    float d = length(normalize(cameraPosition) - normalize(position));
    float opacity = clamp(d / 100, 0, 1);

    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f - opacity);
}