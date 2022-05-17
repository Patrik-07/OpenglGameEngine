#pragma once

#include "Camera.h"
#include "../Opengl/Uniform/UniformProvider.h"
#include "../Utility/Resources.h"

class GridUniformProvider : public UniformProvider {
public:
    GridUniformProvider(Camera& camera, ShaderProgram& shaderProgram) : UniformProvider("camera", shaderProgram) {
        setUniform("position", new UNIFORM::GL_3_F_V(glm::value_ptr(camera.position)));
        setUniform("view", new UNIFORM::GL_MATRIX_4F_V(glm::value_ptr(camera.viewMatrix)));
        setUniform("projection", new UNIFORM::GL_MATRIX_4F_V(glm::value_ptr(camera.projectionMatrix)));
    }
};

class Grid {
    GridUniformProvider gridUniformProvider;
    ShaderProgram gridShader;

public:
    Grid(Camera& camera) : gridShader(
        RESOURCE::SHADER::GRID_VS,
        RESOURCE::SHADER::GRID_FS
    ), gridUniformProvider(camera, gridShader) {}

    void draw(Camera& camera) {
        gridUniformProvider.updateShader();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
};