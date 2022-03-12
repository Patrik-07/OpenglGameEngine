#pragma once

#include <vector>
#include "Uniform.h"
#include "ShaderProgram.h"

class UniformProvider {
    ShaderProgram shaderProgram;
    std::vector<UniformBase> uniforms;

public:
    UniformProvider(const char* structName, ShaderProgram shaderProgram);

    template<typename T>
    void addUniform(Uniform<T> uniform) {
        uniforms.push_back(uniform);
    }

    void update() {
        for (UniformBase uniform : uniforms) {
            shaderProgram.setUniform(uniform.name, uniform.getData<>());
        }
    }
};