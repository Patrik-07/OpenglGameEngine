#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_2_UI : public ScalarUniformValue<unsigned int> {
    public:
        GL_2_UI(unsigned int v0, unsigned int v1) : ScalarUniformValue<unsigned int>(v0, v1) {}
        void set(int location) const override {
            glUniform2ui(location, v0, v1);
        }
    };
}