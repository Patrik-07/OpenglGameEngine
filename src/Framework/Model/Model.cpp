#include "Model.h"

Model::Model(const std::vector<Mesh>& meshes, ShaderProgram& shaderProgram) : shaderProgram(shaderProgram) {
    this->meshes = meshes;
}

void Model::draw() const {
    for (Mesh m : meshes) {
        m.draw(shaderProgram);
    }
}
