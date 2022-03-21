#pragma once

#include "Geometry.h"
#include "Material.h"

// TODO remove additional dependencies
#include "../Opengl/Shader/ShaderProgram.h"
#include "../Opengl/Texture/Texture.h"

class Mesh {
public:
    Geometry geometry;
    Material material;

public:
    Mesh(const Geometry& geometry, Material material);
    void draw(ShaderProgram& shaderProgram);
};

