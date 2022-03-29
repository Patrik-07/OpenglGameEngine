#pragma once

struct VertexBoneData {

    unsigned int vertexID;

    // model to bone space
    glm::mat4 offsetMatrix;
};