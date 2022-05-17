#include "Material.h"

#include "../opengl/uniform/Uniforms.h"

Material::Material(std::vector<Texture> textures) {
    this->textures = std::move(textures);
}

void Material::update(ShaderProgram& shaderProgram) {
    if (!textures.empty()) {
        shaderProgram.setUniform("enableTexture", true);
    } else shaderProgram.setUniform("enableTexture", false);

    for (int i = 0; i < textures.size(); i++) {
        std::string textureTypeName = "";
        switch (textures[i].type) {
            case Texture::DIFFUSE: textureTypeName.append("diffuseMap"); break;
            case Texture::SPECULAR: textureTypeName.append("specularMap"); break;
            case Texture::AMBIENT: textureTypeName.append("ambientMap"); break;
        }
        shaderProgram.setUniform(textureTypeName.c_str(), textures[i].ID, i);
    }
//    static Texture t = Texture::create("models/plane/wood.png", Texture::DIFFUSE);
//    shaderProgram.setUniform("depthMap", t.ID, 1);

    glActiveTexture(GL_TEXTURE0);
}
