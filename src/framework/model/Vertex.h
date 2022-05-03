#pragma once

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/ext/matrix_float4x4.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;

    int boneIDs[4];
    float weights[4];

    int boneCount;
};