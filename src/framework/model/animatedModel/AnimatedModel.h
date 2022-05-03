#pragma once

#include <vector>
#include <string>

#include "../Mesh.h"
#include "Skeleton.h"

class Model {
private:
    std::vector<Mesh> meshes;
    std::map<std::string, VertexBoneData> boneMap;
    int boneCount = 0;
    Skeleton skeleton;

public:
    Model(const std::vector<Mesh>& meshes, std::map<std::string, VertexBoneData> boneMap, int boneCount);

    void draw(ShaderProgram& shaderProgram) const;

    auto& getBoneMap() {
        return boneMap;
    }

    int& getBoneCount() {
        return boneCount;
    }
};