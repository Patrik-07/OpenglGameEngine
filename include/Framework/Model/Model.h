#pragma once

#include <vector>
#include <string>

#include "Mesh.h"

// TODO remove additional dependencies
#include "Framework/Opengl/Shader/ShaderProgram.h"

class Model {
private:
    std::vector<Mesh> meshes;
    std::string directory; // ???

public:
    Model(const std::vector<Mesh>& meshes, const std::string& directory);

    void draw(ShaderProgram& shaderProgram);
};