#pragma once

#include <string>

#include "Glew/glew.h"

#include "../../Utility/Image.h"

class Texture {
public:
    unsigned int ID = 0;
    unsigned int type;
    std::string path;

    static Texture create(const char* imagePath, unsigned int type);

    static constexpr const unsigned int DIFFUSE = 0;
    static constexpr const unsigned int SPECULAR = 1;
    static constexpr const unsigned int AMBIENT = 2;

private:
    explicit Texture(const char* imagePath, unsigned int type);
};