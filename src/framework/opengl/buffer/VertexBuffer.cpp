#include "VertexBuffer.h"
#include "../../model/Vertex.h"

VertexBuffer::VertexBuffer(const void* vertices, size_t size) : Buffer() {
    glGenBuffers(1, &ID);

    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer VertexBuffer::create(const void *vertices, size_t size) {
    return VertexBuffer(vertices, size);
}

void VertexBuffer::setLayout(std::initializer_list<VertexAttribute> layout) const {
    std::vector<VertexAttribute> attributes = layout;

    size_t stride = 0;
    size_t offset[attributes.size() + 1];
    offset[0] = 0;
    for (int i = 0; i < attributes.size(); i++) {
        VertexAttribute va = attributes[i];

        size_t size = va.size * sizeof(types.at(va.type));

//        stride += size;
        offset[i + 1] = offset[i] + size;
    }
    stride = sizeof(Vertex);

    for (int i = 0; i < attributes.size(); i++) {
        VertexAttribute va = attributes[i];

        int location = va.location != -1 ? va.location : i;
        glVertexAttribPointer(location, va.size, va.type, GL_FALSE, stride, (void*)offset[i]);
        glEnableVertexAttribArray(location);
    }
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const std::map<GLenum, size_t> VertexBuffer::types = {
    { GL_BYTE, sizeof(signed char) },
    { GL_UNSIGNED_BYTE, sizeof(unsigned char) },
    { GL_SHORT, sizeof(short) },
    { GL_UNSIGNED_SHORT, sizeof(unsigned short) },
    { GL_INT, sizeof(int) },
    { GL_UNSIGNED_INT, sizeof(unsigned int) },
    { GL_HALF_FLOAT, sizeof(unsigned short) },
    { GL_FLOAT, sizeof(float) },
    { GL_DOUBLE, sizeof(double) },
    { GL_FIXED, sizeof(int) },
};