#pragma once

#include "ShaderProgram.h"

class UniformBase {
public:
    const char* name;
    template<typename T>
    const T& getData() const;
};

template<typename T>
class Uniform : public UniformBase {
    const T& data;
public:
    Uniform(const char* name, const T& data);
};

template<typename T>
const T &UniformBase::getData() const {
    return Uniform<T>(*this).data;
}