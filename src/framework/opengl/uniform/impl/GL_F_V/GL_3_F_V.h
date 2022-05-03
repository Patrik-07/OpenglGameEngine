#pragma once

#include "../../base/VectorUniformValue.h"

namespace UNIFORM {
    class GL_3_F_V : public VectorUniformValue<float> {
    public:
        using VectorUniformValue<float>::VectorUniformValue;
        void set(int location) const override {
            glUniform3fv(location, count, value);
        }
    };
}