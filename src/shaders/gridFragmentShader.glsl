#version 330 core

in vec3 position;

out vec4 FragColor;

uniform vec3 cameraPosition;

bool equal(float a, float b) {
    float eps = 0.001f;
    return abs(a - b) > eps;
}

void main() {
    float d = length(normalize(cameraPosition) - normalize(position));
    float opacity = clamp(d / 100, 0, 1);
    vec3 color = vec3(1.0f, 1.0f, 1.0f);

    if (!equal(position.x, 0.0f)) {
        color = vec3(0.0f, 1.0f, 0.0f);
    }

    if (!equal(position.z, 0.0f)) {
        color = vec3(1.0f, 0.0f, 0.0f);
    }

    FragColor = vec4(color,1.0f - opacity);
}