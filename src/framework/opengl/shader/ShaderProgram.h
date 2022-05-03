#pragma once

#include "Glew/glew.h"

#include "Shader.h"
#include "../Uniform/Base/UniformBase.h"

class ShaderProgram {
public:
    unsigned int ID = 0;

    explicit ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath = nullptr);

    void use() const;

    void setUniform(Uniform& uniform) const {
        int location = glGetUniformLocation(ID, uniform.name.c_str());
        if (location != -1) {
            uniform.set(location);
        } else printf("Invalid uniform name.\n");
    }

//    void setUniform(const std::string& name, bool value) const;
    void setUniform(const std::string& name, int value) const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, const float* vector, unsigned int size) const;
    void setUniform(const std::string& name, const float* matrix) const;
    void setUniform(const std::string& name, unsigned int textureID, int textureUnit = 0) const;

    ~ShaderProgram();

private:
//    void setUniform(const std::string& name, bool value) const;
//    void setUniform(const std::string& name, int value) const;
//    void setUniform(const std::string& name, float value) const;
//    void setUniform(const std::string& name, const float* vector, unsigned int size) const;
//    void setUniform(const std::string& name, const float* matrix) const;
//    void setUniform(const std::string& name, unsigned int textureID, int textureUnit = 0) const;
//    void setUniform(const std::string& name, Texture) const;
};