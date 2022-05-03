#pragma once

#include "../Opengl/Uniform/Uniforms.h"
#include "../Opengl/Uniform/Base/MatrixUniformValue.h"
#include "../Model/Model.h"

class SceneObject : public UniformProvider {
    Model& model;
    ShaderProgram& shaderProgram;

    glm::mat4 modelMatrix;
public:
    SceneObject(Model& model, ShaderProgram& shaderProgram) : model(model), shaderProgram(shaderProgram), UniformProvider("mvp", shaderProgram) {
        modelMatrix = glm::mat4(1.0f);
        setUniform("model", new UNIFORM::GL_MATRIX_4F_V(glm::value_ptr(modelMatrix)));
    }

    void translate(glm::vec3 v) {
        modelMatrix = glm::translate(modelMatrix, v);
    }

    void rotate(float angle, glm::vec3 v) {
        modelMatrix = glm::rotate(modelMatrix, angle, v);
    }

    void scale(glm::vec3 s) {
        modelMatrix = glm::scale(modelMatrix, s);
    }

    void draw() {
        model.draw(shaderProgram);
    }
};