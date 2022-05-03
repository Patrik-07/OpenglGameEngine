#pragma once

#include "Glew/glew.h"

class VertexAttribute {
public:
    const unsigned int size;
    const GLenum type;
    const int location;

    VertexAttribute(GLenum type, unsigned int size, int location = -1);

    static constexpr const unsigned int BYTE =  GL_BYTE;
    static constexpr const unsigned int UNSIGNED_BYTE = GL_UNSIGNED_BYTE;
    static constexpr const unsigned int SHORT = GL_SHORT;
    static constexpr const unsigned int UNSIGNED_SHORT = GL_UNSIGNED_SHORT;
    static constexpr const unsigned int INT = GL_INT;
    static constexpr const unsigned int UNSIGNED_INT = GL_UNSIGNED_INT;
    static constexpr const unsigned int HALF_FLOAT =  GL_HALF_FLOAT;
    static constexpr const unsigned int FLOAT = GL_FLOAT;
    static constexpr const unsigned int DOUBLE = GL_DOUBLE;
    static constexpr const unsigned int FIXED = GL_FIXED;
};