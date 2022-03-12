#pragma once

#include <vector>
#include <string>

#include "../Opengl/Shader/ShaderProgram.h"
#include "../Opengl/Texture.h"

#include "Mesh.h"

class Model {
private:
    std::vector<Mesh> meshes;
public:
    ShaderProgram& shaderProgram;

    Model(const std::vector<Mesh>& meshes, ShaderProgram& shaderProgram);

    template<class ModelLoader>
    static Model load(const char* modelPath, ShaderProgram& shaderProgram) {
        ModelLoader loader;
        return loader.load(modelPath, shaderProgram);
    }

    void draw() const;
};