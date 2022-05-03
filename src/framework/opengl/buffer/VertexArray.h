#pragma once

#include "Glew/glew.h"

#include "Buffer.h"

class VertexArray : Buffer {
public:
    static VertexArray create();

    void bind() const override;
    void unbind() const override;

private:
    VertexArray();
};

