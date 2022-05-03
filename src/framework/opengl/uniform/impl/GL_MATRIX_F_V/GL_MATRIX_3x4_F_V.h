#pragma once

#include "../../base/MatrixUniformValue.h"

namespace UNIFORM {
    class GL_MATRIX_3x4_F_V : public MatrixUniformValue {
    public:
        using MatrixUniformValue::MatrixUniformValue;
        void set(int location) const override {
            glUniformMatrix3x4fv(location, count, transpose, value);
        }
    };
}