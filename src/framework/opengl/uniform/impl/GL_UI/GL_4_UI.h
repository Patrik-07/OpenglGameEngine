#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_4_UI : public ScalarUniformValue<unsigned int> {
    public:
        GL_4_UI(unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) : ScalarUniformValue<unsigned int>(v0, v1, v2, v3) {}
        void set(int location) const override {
            glUniform4ui(location, v0, v1, v2, v3);
        }
    };
}