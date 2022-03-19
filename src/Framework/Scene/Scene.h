#pragma once

#include <vector>

#include "Grid.h"
#include "SceneObject.h"
#include "Camera.h"

#include "../Opengl/Shader/ShaderProgram.h"

class Scene  {
    std::vector<SceneObject*> objects;
    Camera& camera;

public:
    int width, height;
    Grid grid;

    explicit Scene(int& w, int& h, Camera& camera) : grid(camera), camera(camera) {
        resize(w, h);
    }

    void addSceneObject(SceneObject& sceneObject) {
        objects.push_back(&sceneObject);
    }

    void draw() {
        for (SceneObject* object : objects) {
            object->draw();
        }
        grid.draw(camera);
    }

    void resize(int w, int h) {
        width = w; height = h;
        camera.setAspectRatio(w / h);
    }

    void update() {
        for (SceneObject* object : objects) {
            object->update();
        }
        camera.update();
    }
};