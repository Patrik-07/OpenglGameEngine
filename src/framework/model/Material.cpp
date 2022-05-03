#include "Material.h"

#include "../Opengl/Uniform/Uniforms.h"

Material::Material(std::vector<Texture> textures) {
    this->textures = std::move(textures);
}

void Material::update(ShaderProgram& shaderProgram) {
    if (!textures.empty()) {
        shaderProgram.setUniform("enableTexture", true);
    } else shaderProgram.setUniform("enableTexture", false);

    for (int i = 0; i < textures.size(); i++) {
        std::string textureTypeName = "material.";
        glActiveTexture(GL_TEXTURE0 + i);
        switch (textures[i].type) {
            case Texture::DIFFUSE: textureTypeName.append("diffuseMap");  break;
            case Texture::SPECULAR: textureTypeName.append("specularMap"); break;
            case Texture::AMBIENT: textureTypeName.append("ambientMap"); break;
        }
        shaderProgram.setUniform(textureTypeName.c_str(), textures[i].ID, i);
        glBindTexture(GL_TEXTURE_2D, textures[i].ID);
    }

    glActiveTexture(GL_TEXTURE0);
}
