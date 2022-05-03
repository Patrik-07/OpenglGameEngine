#pragma once

struct VertexBoneData {
    int id; // in poses
    glm::mat4 offsetMatrix; // model to bone space
};