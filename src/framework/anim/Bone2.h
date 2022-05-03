#pragma  once

#include <string>
#include <vector>
#include "glm/ext/matrix_float4x4.hpp"
#include "VertexData.h"

class Bone2 {
public:
    unsigned int id;
    std::string name;

    glm::mat4 offsetMatrix;
    glm::mat4 parentMatrix;

    std::vector<Bone2> children;
};