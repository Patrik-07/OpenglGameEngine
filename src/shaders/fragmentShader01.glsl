#version 330 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex;
uniform bool enableTexture;

void main() {
    if (enableTexture) {
        FragColor = texture(tex, texCoord);
    } else FragColor = vec4(0.83f, 0.36f, 0.36f, 1.0f);
}