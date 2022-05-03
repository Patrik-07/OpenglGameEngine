#pragma once

#include "../../base/VectorUniformValue.h"

namespace UNIFORM {
    class GL_2_UI_V : public VectorUniformValue<unsigned int> {
    public:
        using VectorUniformValue<unsigned int>::VectorUniformValue;
        void set(int location) const override {
            glUniform2uiv(location, count, value);
        }
    };
}