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
    std::map<std::string, VertexBoneData> boneData;

public:
    Geometry(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::map<std::string, VertexBoneData>& boneData);
    void draw() const;
};