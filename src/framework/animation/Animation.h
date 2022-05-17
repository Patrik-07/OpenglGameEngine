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

#include "../model/VertexBoneData.h"
#include "Bone.h"
#include "../model/Model.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

struct AssimpNodeData
{
    glm::mat4 transformation;
    std::string name;
    int childrenCount;
    std::vector<AssimpNodeData> children;
};

class Animation {
    int ticks;
public:
    float duration;
    std::vector<Bone> bones;
    AssimpNodeData root;
    std::map<std::string, VertexBoneData> vertexBoneMap;

    Animation(const std::string& animationPath, Model* model) {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(animationPath, aiProcess_Triangulate);

        aiAnimation* animation = scene->mAnimations[2];
        duration = animation->mDuration;
        ticks = animation->mTicksPerSecond * 0.2f;

        readHierarchyData(root, scene->mRootNode);
        processBones(animation, *model);
    }

    Bone* findBone(const std::string& name) {
        auto iter = std::find_if(
            bones.begin(),
            bones.end(),
            [&](const Bone& Bone) { return Bone.getBoneName() == name; }
        );
        if (iter == bones.end()) return nullptr;
        else return &(*iter);
    }

    inline float getTicks() { return ticks; }

    inline const AssimpNodeData& getRootNode() { return root; }

    inline const std::map<std::string,VertexBoneData>& getBoneIDMap() {
        return vertexBoneMap;
    }

private:
    void processBones(const aiAnimation* animation, Model& model) {
        int size = animation->mNumChannels;

        auto& boneMap = model.getBoneMap();
        int& boneCount = model.getBoneCount();

        for (int i = 0; i < size; i++){
            auto channel = animation->mChannels[i];

            std::string boneName = channel->mNodeName.data;
            bones.push_back(Bone(channel->mNodeName.data,channel));
        }

        vertexBoneMap = boneMap;
    }

    void readHierarchyData(AssimpNodeData& dest, const aiNode* src) {
        assert(src);

        dest.name = src->mName.data;
        dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
        dest.childrenCount = src->mNumChildren;

        for (int i = 0; i < src->mNumChildren; i++) {
            AssimpNodeData newData;
            readHierarchyData(newData, src->mChildren[i]);
            dest.children.push_back(newData);
        }
    }
};