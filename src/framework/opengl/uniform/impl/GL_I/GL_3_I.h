#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_3_I : public ScalarUniformValue<int> {
    public:
        GL_3_I(int v0, int v1, int v2) : ScalarUniformValue<int>(v0, v1, v2) {}
        void set(int location) const override {
            glUniform3i(location, v0, v1, v2);
        }
    };
}