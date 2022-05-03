#pragma once

#include "../../base/MatrixUniformValue.h"

namespace UNIFORM {
    class GL_MATRIX_4x2_F_V : public MatrixUniformValue {
    public:
        using MatrixUniformValue::MatrixUniformValue;
        void set(int location) const override {
            glUniformMatrix4x2fv(location, count, transpose, value);
        }
    };
}