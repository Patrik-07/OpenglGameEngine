#pragma once

#include "VectorUniformValue.h"

class MatrixUniformValue : public VectorUniformValue<float> {
public:
    bool transpose;

    MatrixUniformValue(const float* value, unsigned int count = 1, bool transpose = false) : VectorUniformValue<float>(value, count) {
        this->transpose = transpose;
    }

    virtual void set(int location) {}
};