#pragma once

#include <vector>

#include "../Opengl/Texture/Texture.h"
#include "../Opengl/Shader/ShaderProgram.h"
#include "../Opengl/Uniform/Base/UniformBase.h"
#include "../Opengl/Uniform/UniformProvider.h"

class Material {
public:
    std::vector<Texture> textures;

    Material() {}

    explicit Material(std::vector<Texture> textures);
    void update(ShaderProgram& shaderProgram);
};