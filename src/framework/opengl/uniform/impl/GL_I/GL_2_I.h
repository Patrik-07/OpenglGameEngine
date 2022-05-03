#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_2_I : public ScalarUniformValue<int> {
    public:
        GL_2_I(int v0, int v1) : ScalarUniformValue<int>(v0, v1) {}
        void set(int location) const override {
            glUniform2i(location, v0, v1);
        }
    };
}