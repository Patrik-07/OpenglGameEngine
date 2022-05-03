#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_4_I : public ScalarUniformValue<int> {
    public:
        GL_4_I(int v0, int v1, int v2, int v3) : ScalarUniformValue<int>(v0, v1, v2, v3) {}
        void set(int location) const override {
            glUniform4i(location, v0, v1, v2, v3);
        }
    };
}