#pragma once

#include <iostream>
#include <vector>

#include "Base/UniformBase.h"
#include "../Shader/ShaderProgram.h"
#include "Uniforms.h"

class UniformProvider {
    std::string structName;
    std::vector<Uniform> uniforms;
    ShaderProgram& shaderProgram;

public:
    UniformProvider(const std::string& structName, ShaderProgram& shaderProgram) : structName(structName), shaderProgram(shaderProgram) {}

    virtual void update() {
        int count = 0;
        glGetProgramiv(shaderProgram.ID, GL_ACTIVE_UNIFORMS, &count);

        GLsizei length;
        GLint size;
        GLenum type;
        const GLsizei bufSize = 16;
        GLchar name[bufSize];

        shaderProgram.use();
        for (int i = 0; i < count; i++) {
            glGetActiveUniform(shaderProgram.ID, (GLuint)i, bufSize, &length, &size, &type, name);
            for (Uniform uniform : uniforms) {
                if (uniform.name.compare(name)) {
                    shaderProgram.setUniform(uniform);
                }
            }
        }
    }

protected:
    void setUniform(const std::string& name, const UniformValue* uniformValue) {
        Uniform uniform(structName + "." + name, uniformValue);
        uniforms.push_back(uniform);
    }

    ~UniformProvider() {
        for (Uniform uniform : uniforms) {
            delete uniform.value;
        }
    }
};