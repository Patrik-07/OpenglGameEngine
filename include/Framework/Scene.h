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
        grid.draw(camera.getViewMatrix(), camera.getProjectionMatrix(), camera.getPosition());
        for (SceneObject* object : objects) {
            object->draw();
        }
    }

    void resize() {
        update();
    }

    void update() {
        camera.update();
        refresh();
    }

private:
    void refresh() override {
        for (SceneObject* object : objects) {
            object->setViewMatrix(camera.getViewMatrix());
            object->setProjectionMatrix(camera.getProjectionMatrix());
        }
    }
};