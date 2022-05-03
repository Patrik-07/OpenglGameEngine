#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_3_F : public ScalarUniformValue<float> {
    public:
        GL_3_F(float v0, float v1, float v2) : ScalarUniformValue<float>(v0, v1, v2) {}
        void set(int location) const override {
            glUniform3f(location, v0, v1, v2);
        }
    };
}