#pragma once

#include "glm/vec3.hpp"

class Keyframe {
    float timeStamp;

    glm::vec3 positionValue;
    struct ScaleKeyframe : public Keyframe<glm::vec3> {};
    struct RotationKeyframe : public Keyframe<glm::quat> {};
};