#version 330 core
layout (location = 0) in vec3 vertex;

out vec3 position;

struct MVP {
    mat4 model;
    mat4 view;
    mat4 projection;
};

uniform MVP mvp;

void main() {
    vec4 pos = mvp.projection * mvp.view * mvp.model * vec4(vertex, 1.0f);
    gl_Position = pos;
    position = vertex;
}