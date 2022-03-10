#pragma once

#include <fstream>
#include <sstream>

#include "Glew/glew.h"

class Shader {
public:
    unsigned int ID = 0;

    Shader(const char* shaderPath, GLenum shaderType);
    ~Shader();
};