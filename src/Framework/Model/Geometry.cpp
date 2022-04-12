#include "Geometry.h"

Geometry::Geometry(const std::vector<Vertex>& vertices, const std::vector<unsigned int> &indices) {
    this->vertices = vertices;
    this->indices = indices;

    VertexBuffer vertexBuffer = VertexBuffer::create(&this->vertices[0], this->vertices.size() * sizeof(Vertex));
    vertexBuffer.setLayout({
       { VertexAttribute::FLOAT, 3 },
       { VertexAttribute::FLOAT, 3 },
       { VertexAttribute::FLOAT, 2 },
       { VertexAttribute::INT, 4 },
       { VertexAttribute::FLOAT, 4 },
    });
    vertexBuffer.unbind();

    ElementBuffer elementBuffer = ElementBuffer::create(&this->indices[0], this->indices.size() * sizeof(unsigned int));

    vertexArray.unbind();
    elementBuffer.unbind();
}

void Geometry::draw() const {
    vertexArray.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vertexArray.unbind();
}