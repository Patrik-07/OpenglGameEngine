#pragma once

class Grid {
    ShaderProgram gridShader;
public:
    Grid() : gridShader(
        "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\Shaders\\gridVertexShader.glsl",
        "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\Shaders\\gridFragmentShader.glsl"
   ) {}

    void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 cameraPosition) {
        gridShader.use();

        gridShader.setUniform("cameraPosition", glm::value_ptr(cameraPosition), 3);
        gridShader.setUniform("mvp.view", glm::value_ptr(view));
        gridShader.setUniform("mvp.projection", glm::value_ptr(projection));

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
};