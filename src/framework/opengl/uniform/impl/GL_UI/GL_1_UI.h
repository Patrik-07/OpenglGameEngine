#pragma once

#include "../../base/ScalarUniformValue.h"

namespace UNIFORM {
    class GL_1_UI : public ScalarUniformValue<unsigned int> {
    public:
        GL_1_UI(unsigned int v0) : ScalarUniformValue<unsigned int>(v0) {}
        void set(int location) const override {
            glUniform1ui(location, v0);
        }
    };
}