#pragma once

#include <vector>

#include "Framework/Opengl/Texture.h"

class Material {
public:
    std::vector<Texture> textures;

    explicit Material(std::vector<Texture> textures);
};