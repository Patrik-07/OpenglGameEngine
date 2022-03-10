#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath, const char *geometryShaderPath) {
    Shader vertexShader(vertexShaderPath, GL_VERTEX_SHADER);
    Shader fragmentShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    Shader geometryShader(geometryShaderPath, GL_GEOMETRY_SHADER);

    ID = glCreateProgram();

    glAttachShader(ID, vertexShader.ID);
    glAttachShader(ID, fragmentShader.ID);
    if (geometryShader.ID != 0)
        glAttachShader(ID, geometryShader.ID);

    glLinkProgram(ID);
    glUseProgram(ID);
}

void ShaderProgram::use() const {
    glUseProgram(ID);
}

void ShaderProgram::setUniform(const std::string &name, bool value) const {
    int location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform1i(location, value);
    } else printf("Invalid uniform name.\n");
}

void ShaderProgram::setUniform(const std::string &name, int value) const {
    int location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform1i(location, value);
    } else printf("Invalid uniform name.\n");
}

void ShaderProgram::setUniform(const std::string &name, float value) const {
    int location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniform1f(location, value);
    } else printf("Invalid uniform name.\n");
}

void ShaderProgram::setUniform(const std::string &name, const float *vector, unsigned int size) const {
    if (size <= 4) {
        int location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniform3fv(location, 1, vector);
        } else printf("Invalid uniform name.\n");
    } else printf("Invalid vector length.\n");
}

void ShaderProgram::setUniform(const std::string &name, const float *matrix) const {
    int location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
    } else printf("Invalid uniform name.\n");
}

void ShaderProgram::setUniform(const std::string &name, unsigned int textureID, int textureUnit) const {
    int location = glGetUniformLocation(ID, name.c_str());
    if (location != -1) {
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glUniform1i(location, textureUnit);
        glBindTexture(GL_TEXTURE_2D, textureID);
    } else printf("Invalid uniform name.\n");
}

ShaderProgram::~ShaderProgram() {
    if (ID != 0)
        glDeleteProgram(ID);
}