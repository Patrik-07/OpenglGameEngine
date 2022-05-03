#pragma once

#include "../../base/MatrixUniformValue.h"

namespace UNIFORM {
    class GL_MATRIX_2x4_F_V : public MatrixUniformValue {
    public:
        using MatrixUniformValue::MatrixUniformValue;
        void set(int location) const override {
            glUniformMatrix2x4fv(location, count, transpose, value);
        }
    };
}