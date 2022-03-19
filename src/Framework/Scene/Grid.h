#pragma once

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
        "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\Shaders\\gridVertexShader.glsl",
        "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\Shaders\\gridFragmentShader.glsl"
    ), gridUniformProvider(camera, gridShader) {}

    void draw(Camera& camera) {
        gridUniformProvider.update();
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
};