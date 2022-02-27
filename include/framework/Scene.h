#pragma once

class Scene : IScene {
    std::vector<SceneObject*> objects;

    const char* gridVSPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\gridVertexShader.glsl";
    const char* gridFSPath = "C:\\Users\\PatrikSanta\\Prog\\C++\\Imgui\\src\\shaders\\gridFragmentShader.glsl";

    ShaderProgram gridShader;
    Grid grid;
public:
    Camera camera;
    explicit Scene() : camera(this), gridShader(gridVSPath, gridFSPath), grid(20) {}

    void addSceneObject(SceneObject& sceneObject) {
        sceneObject.setViewMatrix(camera.getViewMatrix());
        sceneObject.setProjectionMatrix(camera.getProjectionMatrix());
        objects.push_back(&sceneObject);
    }

    void draw() {
        drawGrid();
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->draw();
        }
    }

    void resize() {
        refresh();
    }

private:
    void refresh() override {
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->setViewMatrix(camera.getViewMatrix());
            objects[i]->setProjectionMatrix(camera.getProjectionMatrix());
        }
    }

    void drawGrid() {
        gridShader.use();

        gridShader.setUniform("mvp.model", glm::scale(glm::mat4(1.0f), glm::vec3(10.0f)));
        gridShader.setUniform("mvp.view", camera.getViewMatrix());
        gridShader.setUniform("mvp.projection", camera.getProjectionMatrix());

        glm::vec3 cameraPosition = camera.getPosition();
        int y = (int)cameraPosition.y;
        if (y > 60) {
            grid.reset(12);
        } else if (y > 30) {
            grid.reset(16);
        } else grid.reset(20);

        gridShader.setUniform("cameraPosition", camera.getPosition());
        grid.draw();
    }
};