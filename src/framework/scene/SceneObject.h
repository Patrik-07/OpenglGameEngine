#pragma once

#include "../opengl/uniform/Uniforms.h"
#include "../opengl/uniform/base/MatrixUniformValue.h"
#include "../model/Model.h"
#include "../animation/Animator.h"

class SceneObject : public UniformProvider {
    Model& model;
    ShaderProgram& shaderProgram;
    Animator animator;

    glm::mat4 modelMatrix;

    // TODO make these properties
//    glm::mat3 position;
//    glm::mat3 rotation;
//    glm::mat3 scale;
public:
    SceneObject(Model& model, ShaderProgram& shaderProgram) : model(model), shaderProgram(shaderProgram), UniformProvider("mvp", shaderProgram) {
        modelMatrix = glm::mat4(1.0f);
        setUniform("model", new UNIFORM::GL_MATRIX_4F_V(glm::value_ptr(modelMatrix)));
    }

    void setShader(const ShaderProgram& s) {
        this->shaderProgram = s;
    }

    ShaderProgram& getShader() {
        return shaderProgram;
    }

    // TODO should remove
    void setCurrentAnimation(Animation& animation) {
        animator.setCurrentAnimation(&animation);
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

    virtual void update(float deltaTime) {
        UniformProvider::updateShader();
        if (animator.hasAnimation()) {
            animator.updateAnimation(deltaTime);
            auto poses = animator.getPoses();
            for (int i = 0; i < poses.size(); i++) {
                shaderProgram.setUniform("poses[" + std::to_string(i) + "]", glm::value_ptr(poses[i]));
            }
        }
    }
};