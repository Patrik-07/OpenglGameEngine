#pragma once

class SceneObject : UniformProvider {
    Model& model;

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
public:
    SceneObject(Model& model) : model(model), UniformProvider("mvp", model.shaderProgram) {
        addUniform(Uniform<glm::mat4>("model", modelMatrix));

        modelMatrix = glm::mat4(1.0f);
        viewMatrix = glm::mat4(1.0f);
        projectionMatrix = glm::mat4(1.0f);
    }

    void moveTo(glm::vec3 v) {
        modelMatrix = glm::translate(glm::mat4(1.0f), v);
    }

    void rotate(float angle, glm::vec3 v) {
        modelMatrix = glm::rotate(modelMatrix, angle, v);
    }

    void scale(glm::vec3 s) {
        modelMatrix = glm::scale(modelMatrix, s);
    }

    void setModelMatrix(glm::mat4 m) {
        modelMatrix = m;
    }

    void setViewMatrix(glm::mat4 m) {
        viewMatrix = m;
    }

    void setProjectionMatrix(glm::mat4 m) {
        projectionMatrix = m;
    }

    void draw() {
        model.shaderProgram.use();

        model.shaderProgram.setUniform("mvp.model", glm::value_ptr(modelMatrix));
        model.shaderProgram.setUniform("mvp.view", glm::value_ptr(viewMatrix));
        model.shaderProgram.setUniform("mvp.projection", glm::value_ptr(projectionMatrix));

        model.draw();
    }
};