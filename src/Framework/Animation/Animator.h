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
#include "Animation.h"
#include "Bone.h"

class Animator {
    std::vector<glm::mat4> poses;
    Animation& animation;
    float currentTimeStamp;
    float deltaTime;

public:
    Animator(Animation& animation) : animation(animation) {
        currentTimeStamp = 0.0f;

        for (int i = 0; i < 100; i++)
            poses.push_back(glm::mat4(1.0f));
    }

    void updateAnimation(float dt) {
        deltaTime = dt;
        currentTimeStamp += animation.getTicksPerSecond() * dt;
        currentTimeStamp = fmod(currentTimeStamp, animation.getDuration());
        calculateBoneTransform(&animation.getRootJoint(), glm::mat4(1.0f));
    }

    std::vector<glm::mat4> getPoses() {
        return poses;
    }

private:
    void calculateBoneTransform(const BoneNode* node, glm::mat4 parentTransform) {
        std::string boneName = node->name;
        glm::mat4 boneTransform = node->transformation;

        Bone* bone = animation.findBone(boneName);

        if (bone) {
            bone->update(currentTimeStamp);
            boneTransform = bone->getBoneTransform();
        }

        glm::mat4 finalBoneTransform = parentTransform * boneTransform;

        std::map<std::string, VertexBoneData> boneMap = animation.getBoneMap();
        if (boneMap.find(boneName) != boneMap.end()) {
            int index = boneMap[boneName].vertexID;
            glm::mat4 offset = boneMap[boneName].offsetMatrix;
            poses[index] = finalBoneTransform * offset;
        }

        for (int i = 0; i < node->childrenCount; i++) {
            calculateBoneTransform(&node->children[i], finalBoneTransform);
        }
    }

};