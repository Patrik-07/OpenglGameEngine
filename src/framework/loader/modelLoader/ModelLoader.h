#pragma once

#include "../../model/Model.h"

class ModelLoader {
public:
    virtual Model load(const std::string& modelPath) = 0;
};