#pragma once

#include "../../base/VectorUniformValue.h"

namespace UNIFORM {
    class GL_4_I_V : public VectorUniformValue<int> {
    public:
        using VectorUniformValue<int>::VectorUniformValue;
        void set(int location) const override {
            glUniform4iv(location, count, value);
        }
    };
}