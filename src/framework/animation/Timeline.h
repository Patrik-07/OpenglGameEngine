#pragma once

#include <vector>

#include "Keyframe.h"

template<typename T>
class Timeline {
public:
    std::vector<T> keyframes;
    virtual glm::mat4 interpolate(float animationTime) = 0;

protected:
    int getIndex(float animationTime) {
        for (int i = 0; i < keyframes.size() - 1; i++) {
            if (animationTime < keyframes[i + 1].timeStamp)
                return i;
        }
        return -1;
    }

    float getScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime) {
        float midWayLength = animationTime - lastTimeStamp;
        float framesDiff = nextTimeStamp - lastTimeStamp;
        float scaleFactor = midWayLength / framesDiff;

        return scaleFactor;
    }
};

class PositionTimeline : public Timeline<PositionKeyframe> {
public:
    glm::mat4 interpolate(float animationTime) override {
        if (1 == keyframes.size())
            return glm::translate(glm::mat4(1.0f), keyframes[0].value);

        int p0Index = getIndex(animationTime);
        int p1Index = p0Index + 1;

        float scaleFactor = getScaleFactor(
            keyframes[p0Index].timeStamp,
            keyframes[p1Index].timeStamp,
            animationTime
        );

        glm::vec3 finalPosition = glm::mix(
            keyframes[p0Index].value,
            keyframes[p1Index].value,
            scaleFactor
        );

        return glm::translate(glm::mat4(1.0f), finalPosition);
    }
};

class RotationTimeline : public Timeline<RotationKeyframe> {
public:
    glm::mat4 interpolate(float animationTime) override {
        if (1 == keyframes.size())
            return glm::toMat4(glm::normalize(keyframes[0].value));

        int p0Index = getIndex(animationTime);
        int p1Index = p0Index + 1;

        float scaleFactor = getScaleFactor(
            keyframes[p0Index].timeStamp,
            keyframes[p1Index].timeStamp,
            animationTime
        );

        glm::quat finalRotation = glm::slerp(
            keyframes[p0Index].value,
            keyframes[p1Index].value,
            scaleFactor
        );

        finalRotation = glm::normalize(finalRotation);
        return glm::toMat4(finalRotation);
    }
};

class ScaleTimeline : public Timeline<ScaleKeyframe> {
public:
    glm::mat4 interpolate(float animationTime) override {
        if (1 == keyframes.size())
            return glm::scale(glm::mat4(1.0f), keyframes[0].value);

        int p0Index = getIndex(animationTime);
        int p1Index = p0Index + 1;

        float scaleFactor = getScaleFactor(
            keyframes[p0Index].timeStamp,
            keyframes[p1Index].timeStamp,
            animationTime
        );

        glm::vec3 finalScale = glm::mix(
            keyframes[p0Index].value,
            keyframes[p1Index].value,
            scaleFactor
        );

        return glm::scale(glm::mat4(1.0f), glm::normalize(finalScale));
    }
};
