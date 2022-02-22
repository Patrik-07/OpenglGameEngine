#pragma once

class Model {
private:
    std::vector<Mesh> meshes;
public:
    Model(std::vector<Mesh> meshes) {
        this->meshes = meshes;
    }

    void draw() {
        for (Mesh m : meshes) {
            m.draw();
        }
    }

    ~Model() {
        for (Mesh &mesh: meshes) {
            mesh.free();
        }
    }
};