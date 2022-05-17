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
    Animation* animation = nullptr;
    float currentTime;

public:
    Animator() {
        currentTime = 0.0;
        for (int i = 0; i < 100; i++) {
            poses.push_back(glm::mat4(1.0f));
        }
    }

    void setCurrentAnimation(Animation* anim) {
        this->animation = anim;
    }

    bool hasAnimation() {
        return animation != nullptr;
    }

    void updateAnimation(float dt) {
        currentTime += animation->getTicks() * dt;
        if (currentTime > animation->duration) {
            currentTime /= animation->duration;
        }
        calculateBoneTransform(&animation->getRootNode(), glm::mat4(1.0f));
    }

    void calculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform) {
        std::string nodeName = node->name;
        glm::mat4 nodeTransform = node->transformation;

        Bone* Bone = animation->findBone(nodeName);

        if (Bone) {
            Bone->update(currentTime);
            nodeTransform = Bone->getBoneTransform();
        }

        glm::mat4 globalTransformation = parentTransform * nodeTransform;

        auto boneInfoMap = animation->getBoneIDMap();

        int index = boneInfoMap[nodeName].id;
        glm::mat4 offset = boneInfoMap[nodeName].offsetMatrix;
        poses[index] = globalTransformation * offset;

        for (int i = 0; i < node->childrenCount; i++) {
            calculateBoneTransform(&node->children[i], globalTransformation);
        }
    }

    std::vector<glm::mat4> getPoses() {
        return poses;
    }
};