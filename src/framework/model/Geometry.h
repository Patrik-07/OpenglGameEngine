#pragma once

#include "../opengl/buffer/VertexArray.h"
#include "../opengl/buffer/VertexBuffer.h"
#include "../opengl/buffer/ElementBuffer.h"

#include "Vertex.h"
#include "VertexBoneData.h"

class Geometry {
public:
    VertexArray vertexArray = VertexArray::create();
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

public:
    Geometry(std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    void draw() const;
};