#pragma once

#include "../../base/VectorUniformValue.h"

namespace UNIFORM {
    class GL_1_F_V : public VectorUniformValue<float> {
    public:
        using VectorUniformValue<float>::VectorUniformValue;
        void set(int location) const override {
            glUniform1fv(location, count, value);
        }
    };
}