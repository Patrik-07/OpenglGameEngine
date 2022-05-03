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
#include "Keyframe.h"
#include "Timeline.h"

class Bone {
    PositionTimeline positionTimeline;
    RotationTimeline rotationTimeline;
    ScaleTimeline scaleTimeline;

    glm::mat4 boneTransform;
    std::string name;
    int m_ID;

public:
    Bone(const std::string &name, const aiNodeAnim *channel) : name(name), boneTransform(1.0f) {
        parsePositionKeyframes(channel);
        parseRotationKeyframes(channel);
        parseScaleKeyFrames(channel);
    }

    void update(float animationTime) {
        glm::mat4 translation = positionTimeline.interpolate(animationTime);
        glm::mat4 rotation = rotationTimeline.interpolate(animationTime);
        glm::mat4 scale = scaleTimeline.interpolate(animationTime);

        boneTransform = translation * rotation * scale;
    }

    glm::mat4 getBoneTransform() { return boneTransform; }
    std::string getBoneName() const { return name; }

private:
    void parsePositionKeyframes(const aiNodeAnim *channel) {
        std::vector<PositionKeyframe> positions;
        int positionKeyCount = channel->mNumPositionKeys;
        for (int i = 0; i < positionKeyCount; i++) {
            aiVector3D aiPosition = channel->mPositionKeys[i].mValue;
            float timeStamp = channel->mPositionKeys[i].mTime;

            PositionKeyframe data;
            data.value = AssimpGLMHelpers::GetGLMVec(aiPosition);
            data.timeStamp = timeStamp;

            positions.push_back(data);
        }
        positionTimeline.keyframes = positions;
    }

    void parseRotationKeyframes(const aiNodeAnim *channel) {
        std::vector<RotationKeyframe> rotations;
        int rotationKeyCount = channel->mNumRotationKeys;
        for (int i = 0; i < rotationKeyCount; i++) {
            aiQuaternion aiOrientation = channel->mRotationKeys[i].mValue;
            float timeStamp = channel->mRotationKeys[i].mTime;

            RotationKeyframe data;
            data.value = AssimpGLMHelpers::GetGLMQuat(aiOrientation);
            data.timeStamp = timeStamp;

            rotations.push_back(data);
        }
        rotationTimeline.keyframes = rotations;
    }

    void parseScaleKeyFrames(const aiNodeAnim *channel) {
        std::vector<ScaleKeyframe> scales;
        int scaleKeyCount = channel->mNumScalingKeys;
        for (int i = 0; i < scaleKeyCount; i++) {
            aiVector3D scale = channel->mScalingKeys[i].mValue;
            float timeStamp = channel->mScalingKeys[i].mTime;

            ScaleKeyframe data;
            data.value = AssimpGLMHelpers::GetGLMVec(scale);
            data.timeStamp = timeStamp;

            scales.push_back(data);
        }
        scaleTimeline.keyframes = scales;
    }
};