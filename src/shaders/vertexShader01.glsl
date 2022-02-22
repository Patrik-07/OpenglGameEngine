#version 330 core
layout (location = 0) in vec3 vertexPositionCoord;
layout (location = 1) in vec3 vertexNormalCoord;
layout (location = 2) in vec2 vertexTextureCoord;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(vertexPositionCoord, 1.0);
    texCoord = vertexTextureCoord;
}