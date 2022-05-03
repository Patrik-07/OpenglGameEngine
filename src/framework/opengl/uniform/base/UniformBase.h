#pragma once

#include "UniformValue.h"

class Uniform {
public:
    const UniformValue* value;
    std::string name;
    Uniform(const std::string &name, const UniformValue* value) : name(name) {
        this->value = value;
    }

    void set(int location) const {
        value->set(location);
    }
};