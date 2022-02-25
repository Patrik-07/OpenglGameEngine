#pragma once

class Model {
private:
    std::vector<Mesh> meshes;
    std::string directory;
public:
    Model(const std::vector<Mesh>& meshes, const std::string& directory) {
        this->meshes = meshes;
        this->directory = directory;
    }

    Model(const Model& model) {
        this->meshes = model.meshes;
        this->directory = model.directory;
    }

    void draw(ShaderProgram& shaderProgram) {
        for (Mesh m : meshes) {
            m.draw(shaderProgram);
        }
    }
};