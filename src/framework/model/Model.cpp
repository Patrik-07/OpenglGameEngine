#include "Model.h"

Model::Model(const std::vector<Mesh>& meshes, std::map<std::string, VertexBoneData> boneMap, int boneCount) {
    this->meshes = meshes;
    this->boneMap = boneMap;
    this->boneCount = boneCount;
}

void Model::draw(ShaderProgram& shaderProgram) const {
    for (Mesh m : meshes) {
        m.draw(shaderProgram);
    }
}
