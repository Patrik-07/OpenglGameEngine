#version 330 core

in vec2 texCoord;

out vec4 FragColor;

struct Material {
    sampler2D diffuseMap;
    sampler2D ambientMap;
    sampler2D specularMap;
};
uniform Material material;
uniform bool enableTexture;

void main() {
    if (enableTexture) {
        FragColor = texture(material.diffuseMap, texCoord);
    } else FragColor = vec4(0.83f, 0.36f, 0.36f, 1.0f);
}