#include "Mesh.h"

Mesh::Mesh(Geometry geometry, Material material) :
    geometry(geometry), material(material) {}

void Mesh::draw(ShaderProgram& shaderProgram) {
    material.update(shaderProgram);
    geometry.draw();
}