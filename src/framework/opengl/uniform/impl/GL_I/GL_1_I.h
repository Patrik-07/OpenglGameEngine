#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_1_I : public ScalarUniformValue<int> {
    public:
        GL_1_I(int v0) : ScalarUniformValue<int>(v0) {}
        void set(int location) const override {
            glUniform1i(location, v0);
        }
    };
}