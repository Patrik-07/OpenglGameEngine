#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &ID);
    glBindVertexArray(ID);
}

VertexArray VertexArray::create() {
    return VertexArray();
}

void VertexArray::bind() const {
    glBindVertexArray(ID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
