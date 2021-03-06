#pragma once

#include "Geometry.h"
#include "Material.h"

// TODO remove additional dependencies
#include "../opengl/shader/ShaderProgram.h"
#include "../opengl/Texture/Texture.h"

class Mesh {
public:
    Geometry geometry;
    Material material;

public:
    Mesh(Geometry geometry, Material material);
    void draw(ShaderProgram& shaderProgram);
};

