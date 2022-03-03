#pragma once

class Scene : public IScene {
    std::vector<SceneObject*> objects;
    Grid grid;
public:
    Camera camera;
    explicit Scene(int& w, int& h) : IScene(w, h), camera(*this) {}

    void addSceneObject(SceneObject& sceneObject) {
        sceneObject.setViewMatrix(camera.getViewMatrix());
        sceneObject.setProjectionMatrix(camera.getProjectionMatrix());
        objects.push_back(&sceneObject);
    }

    void draw() {
        for (int i = 0; i < objects.size(); i++) {
            objects[i]->draw();
        }
        grid.draw(camera.getViewMatrix(), camera.getProjectionMatrix(), camera.getPosition());
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
};