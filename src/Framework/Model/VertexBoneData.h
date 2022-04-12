#pragma once

struct VertexBoneData {
    int vertexID;
    glm::mat4 offsetMatrix; // model to bone space
};