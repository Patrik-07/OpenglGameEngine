#pragma once

#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"

template<typename T>
struct Keyframe {
    T value;
    float timeStamp;
};

struct PositionKeyframe : public Keyframe<glm::vec3> {};
struct ScaleKeyframe : public Keyframe<glm::vec3> {};
struct RotationKeyframe : public Keyframe<glm::quat> {};
