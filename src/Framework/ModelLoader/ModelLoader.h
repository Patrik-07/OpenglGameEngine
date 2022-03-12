#pragma once

#include "../Model/Model.h"

class ModelLoader {
public:
    virtual Model load(const std::string& modelPath, ShaderProgram& shaderProgram) = 0;
};