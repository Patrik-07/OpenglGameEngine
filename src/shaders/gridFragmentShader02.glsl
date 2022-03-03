#version 330 core

in vec2 textureCoord;

out vec4 FragColor;

uniform sampler2D tex;

void main() {
    FragColor = texture(tex, textureCoord);
//    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}