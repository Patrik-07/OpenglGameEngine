#version 330 core

in vec2 texCoord;

out vec4 FragColor;

struct Material {
    sampler2D diffuseMap;
};

uniform bool enableTexture;
uniform Material material;

void main() {
    if (enableTexture) {
        FragColor = texture(material.diffuseMap, texCoord);
    } else FragColor = vec4(0.83f, 0.36f, 0.36f, 1.0f);
}