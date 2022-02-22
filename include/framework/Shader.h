#pragma once

#include <sstream>

class Shader {
    unsigned int ID = 0;
public:
    Shader(const char* shaderPath, GLenum shaderType) {
        if (shaderPath != nullptr) {
            std::ifstream file;
            std::stringstream shaderStream;
            std::string shader;

            file.open(shaderPath);
            shaderStream << file.rdbuf();
            shader = shaderStream.str();

            const char *shaderCode = shader.c_str();

            ID = glCreateShader(shaderType);
            glShaderSource(ID, 1, &shaderCode, nullptr);
            glCompileShader(ID);
        }
    }

    unsigned int getID() const {
        return ID;
    }

    ~Shader() {
        if (ID != 0)
            glDeleteShader(ID);
    }
};