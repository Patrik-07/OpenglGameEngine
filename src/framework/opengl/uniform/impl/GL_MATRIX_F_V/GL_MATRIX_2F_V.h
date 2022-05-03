#pragma once

#include "../../base/MatrixUniformValue.h"

namespace UNIFORM {
    class GL_MATRIX_2F_V : public MatrixUniformValue {
    public:
        using MatrixUniformValue::MatrixUniformValue;
        void set(int location) const override {
            glUniformMatrix2fv(location, count, transpose, value);
        }
    };
}