#include "Model.h"

Model::Model(const std::vector<Mesh>& meshes, std::map<std::string, VertexBoneData> boneMap) {
    this->meshes = meshes;
    this->boneMap = boneMap;
}

void Model::draw(ShaderProgram& shaderProgram) const {
    for (Mesh m : meshes) {
        m.draw(shaderProgram);
    }
}
