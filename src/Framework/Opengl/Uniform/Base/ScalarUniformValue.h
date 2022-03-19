#pragma once

#include "UniformValue.h"

template<typename T>
class ScalarUniformValue : public TemplatedUniformValue<T> {
public:
    T v0, v1, v2, v3;

    ScalarUniformValue(T v0, T v1 = T(), T v2 = T(), T v3 = T()) {
        this->v0 = v0;
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
    }

    virtual void set(int location) {}
};