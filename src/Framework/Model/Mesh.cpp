#include "Mesh.h"

Mesh::Mesh(const Geometry &geometry, Material material) : geometry(geometry), material(std::move(material)) {}

void Mesh::draw(ShaderProgram& shaderProgram) {
    material.update(shaderProgram);
    geometry.draw();
}