#pragma once

#include <vector>
#include <string>

#include "assimp/vector3.h"
#include "assimp/quaternion.h"

#include "glm/ext/quaternion_float.hpp"
#include "glm/ext/quaternion_common.hpp"
#include "glm/gtx/quaternion.hpp"
#include "AssimpGLMHelpers.h"
#include "assimp/anim.h"

struct BonePosition {
    glm::vec3 position;
    float timeStamp;
};

struct BoneRotation {
    glm::quat orientation;
    float timeStamp;
};

struct BoneScale {
    glm::vec3 scale;
    float timeStamp;
};

class Bone {
    std::vector<BonePosition> positions;
    std::vector<BoneRotation> rotations;
    std::vector<BoneScale> scales;
    int positionCount;
    int rotationCount;
    int scaleCount;

    glm::mat4 boneTransform;
    std::string name;
    int ID;

public:
    Bone(const std::string& name, int ID, const aiNodeAnim* channel) : name(name), ID(ID), boneTransform(1.0f) {
        positionCount = channel->mNumPositionKeys;
        for (int i = 0; i < positionCount; i++) {
            aiVector3D aiPosition = channel->mPositionKeys[i].mValue;
            float timeStamp = channel->mPositionKeys[i].mTime;

            BonePosition position = {
                glm::vec3(aiPosition.x, aiPosition.y, aiPosition.z),
                timeStamp
            };

            positions.push_back(position);
        }

        rotationCount = channel->mNumRotationKeys;
        for (int i = 0; i < rotationCount; i++) {
            aiQuaternion aiOrientation = channel->mRotationKeys[i].mValue;
            float timeStamp = channel->mRotationKeys[i].mTime;

            BoneRotation rotation = {
                glm::quat(aiOrientation.w, aiOrientation.x, aiOrientation.y, aiOrientation.z),
                timeStamp
            };

            rotations.push_back(rotation);
        }

        scaleCount = channel->mNumScalingKeys;
        for (int i = 0; i < scaleCount; i++)
        {
            aiVector3D aiScale = channel->mScalingKeys[i].mValue;
            float timeStamp = channel->mScalingKeys[i].mTime;

            BoneScale scale = {
                glm::vec3(aiScale.x, aiScale.y, aiScale.z),
                timeStamp
            };

            scales.push_back(scale);
        }
    }

    void update(float currentTimeStamp) {
        glm::mat4 translation = interpolatePosition(currentTimeStamp);
        glm::mat4 rotation = interpolateRotation(currentTimeStamp);
        glm::mat4 scale = interpolateScale(currentTimeStamp);
        boneTransform = translation * rotation * scale;
    }

    glm::mat4 getBoneTransform() { return boneTransform; }
    std::string getBoneName() const { return name; }
    int getBoneID() { return ID; }

    int getPositionIndex(float currentTimeStamp) {
        for (int i = 0; i < positionCount - 1; i++) {
            if (currentTimeStamp < positions[i + 1].timeStamp)
                return i;
        }
        return -1;
    }

    int getRotationIndex(float currentTimeStamp) {
        for (int i = 0; i < rotationCount - 1; i++) {
            if (currentTimeStamp < rotations[i + 1].timeStamp) {
                return i;
            }
        }
        return -1;
    }

    int getScaleIndex(float currentTimeStamp) {
        for (int i = 0; i < scaleCount - 1; i++) {
            if (currentTimeStamp < scales[i + 1].timeStamp) {
                return i;
            }
        }
        return -1;
    }

private:
    float getScaleFactor(float lastTimeStamp, float nextTimeStamp, float currentTimeStamp) {
        float midWayLength = currentTimeStamp - lastTimeStamp;
        float framesDiff = nextTimeStamp - lastTimeStamp;
        return midWayLength / framesDiff;
    }

    glm::mat4 interpolatePosition(float currentTimeStamp) {
        if (1 == positionCount) {
            return glm::translate(glm::mat4(1.0f), positions[0].position);
        }

        int p0 = getPositionIndex(currentTimeStamp);
        if (p0 == positionCount - 1) {
            return glm::translate(glm::mat4(1.0f), positions[p0].position);
        }

        int p1 = p0 + 1;
        float scaleFactor = getScaleFactor(
            positions[p0].timeStamp,
            positions[p1].timeStamp,
            currentTimeStamp
        );

        glm::vec3 finalPosition = glm::mix(
            positions[p0].position,
            positions[p1].position,
            scaleFactor
        );

        return glm::translate(glm::mat4(1.0f), finalPosition);
    }

    glm::mat4 interpolateRotation(float currentTimeStamp) {
        if (1 == rotationCount) {
            glm::quat rotation = glm::normalize(rotations[0].orientation);
            return glm::toMat4(rotation);
        }

        int r0 = getRotationIndex(currentTimeStamp);
        if (r0 == rotationCount - 1) {
            glm::quat rotation = glm::normalize(rotations[r0].orientation);
            return glm::toMat4(rotation);
        }

        int r1 = r0 + 1;
        float scaleFactor = getScaleFactor(
            rotations[r0].timeStamp,
            rotations[r1].timeStamp,
            currentTimeStamp
        );

        glm::quat finalRotation = glm::slerp(
            rotations[r0].orientation,
            rotations[r1].orientation,
            scaleFactor
        );

        finalRotation = glm::normalize(finalRotation);
        return glm::toMat4(finalRotation);
    }

    glm::mat4 interpolateScale(float currentTimeStamp) {
        if (1 == scaleCount) {
            return glm::scale(glm::mat4(1.0f), scales[0].scale);
        }

        int s0 = getScaleIndex(currentTimeStamp);
        if (s0 == scaleCount - 1) {
            return glm::scale(glm::mat4(1.0f), scales[s0].scale);
        }

        int s1 = s1 + 1;
        float scaleFactor = getScaleFactor(
            scales[s0].timeStamp,
            scales[s1].timeStamp,
            currentTimeStamp
        );

        glm::vec3 finalScale = glm::mix(
            scales[s0].scale,
            scales[s1].scale,
            scaleFactor
        );

        return glm::scale(glm::mat4(1.0f), finalScale);
    }
};