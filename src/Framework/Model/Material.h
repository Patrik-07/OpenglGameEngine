#pragma once

#include <vector>

#include "../Opengl/Texture.h"
#include "../Opengl/Shader/ShaderProgram.h"
#include "../Opengl/Shader/Uniform.h"
#include "../Opengl/Shader/UniformProvider.h"

class Material : UniformProvider {
public:
    std::vector<Texture> textures;

    Material(ShaderProgram shaderProgram) : UniformProvider("material", shaderProgram) {}
//    void setUniforms(std::initializer_list<UniformBase> uniforms) {
//
//    }

    explicit Material(std::vector<Texture> textures);
    void update(ShaderProgram& shaderProgram);
};