#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_4_F : public ScalarUniformValue<float> {
    public:
        GL_4_F(float v0, float v1, float v2, float v3) : ScalarUniformValue<float>(v0, v1, v2, v3) {}
        void set(int location) const override {
            glUniform4f(location, v0, v1, v2, v3);
        }
    };
}