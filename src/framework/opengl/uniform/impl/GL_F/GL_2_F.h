#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_2_F : public ScalarUniformValue<float> {
    public:
        GL_2_F(float v0, float v1) : ScalarUniformValue<float>(v0, v1) {}
        void set(int location) const override {
            glUniform2f(location, v0, v1);
        }
    };
}