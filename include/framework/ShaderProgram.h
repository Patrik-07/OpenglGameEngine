#pragma once

class ShaderProgram {
    unsigned int ID = 0;
public:
    explicit ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometryShaderPath = nullptr) {
        Shader vertexShader(vertexShaderPath, GL_VERTEX_SHADER);
        Shader fragmentShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
        Shader geometryShader(geometryShaderPath, GL_GEOMETRY_SHADER);

        ID = glCreateProgram();

        glAttachShader(ID, vertexShader.getID());
        glAttachShader(ID, fragmentShader.getID());
        if (geometryShader.getID() != 0)
            glAttachShader(ID, geometryShader.getID());

        glLinkProgram(ID);
        glUseProgram(ID);
    }

    void use() const {
        glUseProgram(ID);
    }

    void setUniform(const std::string& name, bool value) const {
        int location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniform1i(location, value);
        } else printf("Invalid uniform name.\n");
    }

    void setUniform(const std::string& name, int value) const {
        int location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniform1i(location, value);
        } else printf("Invalid uniform name.\n");
    }

    void setUniform(const std::string& name, float value) const {
        int location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniform1f(location, value);
        } else printf("Invalid uniform name.\n");
    }

    void setUniform(const std::string& name, const glm::vec2& vec2) const {
        int location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniform2fv(location, 1, glm::value_ptr(vec2));
        } else printf("Invalid uniform name.\n");
    }

    void setUniform(const std::string& name, const glm::vec3& vec3) const {
        int location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniform3fv(location, 1, &vec3.x);
        } else printf("Invalid uniform name.\n");
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec3));
    }

    void setUniform(const std::string& name, const glm::vec4& vec4) const {
        int location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniform4fv(location, 1, glm::value_ptr(vec4));
        } else printf("Invalid uniform name.\n");
    }

    void setUniform(const std::string& name, const glm::mat4& mat4) const {
        int location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
        } else printf("Invalid uniform name.\n");
    }

    void setUniform(const std::string& name, unsigned int textureID, int textureUnit = 0) const {
        int location = glGetUniformLocation(ID, name.c_str());
        if (location != -1) {
            glActiveTexture(GL_TEXTURE0 + textureUnit);
            glUniform1i(location, textureUnit);
            glBindTexture(GL_TEXTURE_2D, textureID);
        } else printf("Invalid uniform name.\n");
    }

    unsigned int getID() const {
        return ID;
    }

    ~ShaderProgram() {
        if (ID != 0)
            glDeleteProgram(ID);
    }
};