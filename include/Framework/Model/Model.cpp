#include "Model.h"

Model::Model(const std::vector<Mesh> &meshes, const std::string &directory) {
    this->meshes = meshes;
    this->directory = directory; // ???
}

void Model::draw(ShaderProgram &shaderProgram) {
    for (Mesh m : meshes) {
        m.draw(shaderProgram);
    }
}