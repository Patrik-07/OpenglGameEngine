#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_3_UI : public ScalarUniformValue<unsigned int> {
    public:
        GL_3_UI(unsigned int v0, unsigned int v1, unsigned int v2) : ScalarUniformValue<unsigned int>(v0, v1, v2) {}
        void set(int location) const override {
            glUniform3ui(location, v0, v1, v2);
        }
    };
}