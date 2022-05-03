#pragma once

#include "../../base/VectorUniformValue.h"

namespace UNIFORM {
    class GL_3_UI_V : public VectorUniformValue<unsigned int> {
    public:
        using VectorUniformValue<unsigned int>::VectorUniformValue;
        void set(int location) const override {
            glUniform3uiv(location, count, value);
        }
    };
}