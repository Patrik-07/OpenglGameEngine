#pragma once

#include <vector>
#include <string>

#include "../Opengl/Texture/Texture.h"

#include "Mesh.h"

class Model {
private:
    std::vector<Mesh> meshes;
    std::map<std::string, VertexBoneData> boneMap;

public:
    Model(const std::vector<Mesh>& meshes, std::map<std::string, VertexBoneData> boneMap);

    template<class ModelLoader>
    static Model load(const char* modelPath) {
        ModelLoader loader;
        return loader.load(modelPath);
    }

    void draw(ShaderProgram& shaderProgram) const;

    auto& getBoneMap() {
        return boneMap;
    }
};