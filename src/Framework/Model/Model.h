#pragma once

#include <vector>
#include <string>

#include "../Opengl/Texture/Texture.h"

#include "Mesh.h"

class Model {
private:
    std::vector<Mesh> meshes;
public:
    Model(const std::vector<Mesh>& meshes);

    template<class ModelLoader>
    static Model load(const char* modelPath, const char* bonePath = "") {
        ModelLoader loader;
        return loader.load(modelPath, bonePath);
    }

    void draw(ShaderProgram& shaderProgram) const;
};