#version 330 core
layout (location = 0) in vec3 vertexPositionCoord;

uniform float w;

void main() {
    gl_Position = vec4(vertexPositionCoord, w);
}