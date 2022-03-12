#pragma once

#include <initializer_list>
#include <vector>
#include <map>

#include "Glew/glew.h"

#include "Buffer.h"
#include "VertexAttribute.h"

class VertexBuffer : public Buffer {
public:
    static VertexBuffer create(const void* vertices, size_t size);
    void setLayout(std::initializer_list<VertexAttribute> layout) const;

    void bind() const override;
    void unbind() const override;

private:
    VertexBuffer(const void* vertices, size_t size);
    static const std::map<GLenum, size_t> types;
};