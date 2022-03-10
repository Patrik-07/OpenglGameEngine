#include "Mesh.h"

Mesh::Mesh(const Geometry &geometry, Material material) : geometry(geometry), material(std::move(material)) {}

void Mesh::draw(ShaderProgram &shaderProgram) {
    if (!material.textures.empty())
        shaderProgram.setUniform("enableTexture", true);
    else shaderProgram.setUniform("enableTexture", false);

    for (int i = 0; i < material.textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        unsigned int type = material.textures[i].type;
        switch (type) {
            case Texture::DIFFUSE: shaderProgram.setUniform("material.diffuseMap", material.textures[i].ID, i); break;
            case Texture::SPECULAR: shaderProgram.setUniform("material.specularMap", material.textures[i].ID, i); break;
            case Texture::AMBIENT: shaderProgram.setUniform("material.ambientMap", material.textures[i].ID, i); break;
        }
    }

    glActiveTexture(GL_TEXTURE0);
    geometry.draw();
}