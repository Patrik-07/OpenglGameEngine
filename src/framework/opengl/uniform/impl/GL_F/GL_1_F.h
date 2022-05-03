#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_1_F : public ScalarUniformValue<float> {
    public:
        GL_1_F(float v0) : ScalarUniformValue<float>(v0) {}
        void set(int location) const override {
            glUniform1f(location, v0);
        }
    };
}