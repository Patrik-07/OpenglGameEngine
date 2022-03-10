#include "ElementBuffer.h"

ElementBuffer::ElementBuffer(const void *indices, size_t size) : Buffer() {
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_DYNAMIC_DRAW);
}

ElementBuffer ElementBuffer::create(const void *indices, size_t size) {
    return ElementBuffer(indices, size);
}

void ElementBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ElementBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
