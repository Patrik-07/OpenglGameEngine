#pragma once

#include <vector>
#include <string>
#include <map>

#include "assimp/vector3.h"
#include "assimp/quaternion.h"

#include "glm/ext/quaternion_float.hpp"
#include "glm/ext/quaternion_common.hpp"
#include "glm/gtx/quaternion.hpp"
#include "AssimpGLMHelpers.h"
#include "assimp/anim.h"
#include "assimp/scene.h"

#include "../Model/VertexBoneData.h"
#include "Bone.h"
#include "../Model/Model.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

struct BoneNode {
    glm::mat4 transformation;
    std::string name;
    int childrenCount;
    std::vector<BoneNode> children;
};

class Animation {
    float duration;
    int ticksPerSecond;
    std::vector<Bone> bones;
    BoneNode rootJoint;
    std::map<std::string, VertexBoneData> boneMap;

public:
    Animation() = default;

    Animation(const std::string& animationPath, Model& model) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);

        aiAnimation* animation = scene->mAnimations[0];

        duration = animation->mDuration;
        ticksPerSecond = animation->mTicksPerSecond;
        processBoneHierarchy(rootJoint, scene->mRootNode);
        processChannels(animation, model);
    }

    Bone* findBone(const std::string& name) {
        for (int i = 0; i < bones.size(); i++) {
            if (bones[i].getBoneName() == name) {
                return &bones[i];
            }
        }
        return nullptr;
    }

    float getDuration() {
        return duration;
    }

    float getTicksPerSecond() {
        return ticksPerSecond;
    }

    const BoneNode& getRootJoint() {
        return rootJoint;
    }

    const std::map<std::string, VertexBoneData>& getBoneMap() {
        return boneMap;
    }

private:
    void processChannels(const aiAnimation* animation, Model& model) {
        boneMap = model.getBoneMap();

        for (int i = 0; i < animation->mNumChannels; i++) {
            aiNodeAnim* channel = animation->mChannels[i];
            std::string boneName = channel->mNodeName.data;

            Bone bone(
                channel->mNodeName.C_Str(),
                boneMap[channel->mNodeName.data].vertexID,
                channel
            );

            bones.push_back(bone);
        }
    }

    void processBoneHierarchy(BoneNode& dest, const aiNode* src) {
        dest.name = src->mName.data;
        dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
        dest.childrenCount = src->mNumChildren;

        for (int i = 0; i < src->mNumChildren; i++) {
            BoneNode newData;
            processBoneHierarchy(newData, src->mChildren[i]);
            dest.children.push_back(newData);
        }
    }
};