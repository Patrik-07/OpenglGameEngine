#pragma once

#include "../Opengl/Buffer/VertexArray.h"
#include "../Opengl/Buffer/VertexBuffer.h"
#include "../Opengl/Buffer/ElementBuffer.h"

#include "Vertex.h"
#include "VertexBoneData.h"

class Geometry {
public:
    VertexArray vertexArray = VertexArray::create();
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

public:
    Geometry(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    void draw() const;
};