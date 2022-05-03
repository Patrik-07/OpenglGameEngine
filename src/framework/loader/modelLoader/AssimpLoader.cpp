#include "AssimpLoader.h"
#include "../../model/animatedModel/Skeleton.h"

Model AssimpLoader::load(const std::string& modelPath) {
    directory = "";
    loadedTextures.clear();

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

    directory = modelPath.substr(0, modelPath.find_last_of('\\'));

    aiNode *root = scene->mRootNode;
    processNode(root, scene);

    return {meshes, boneDataMap, boneCount};
}

void AssimpLoader::processNode(aiNode *node, const aiScene *scene) {
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];

        Mesh mesh = processMesh(aiMesh, scene);
        meshes.push_back(mesh);
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh AssimpLoader::processMesh(aiMesh *mesh, const aiScene *scene) {
    Geometry geometry = processGeometry(mesh);
    Material material = processMaterial(mesh, scene);

    return {geometry, material};
}

void addVertexBoneData(Vertex& vertex, int boneID, float weight) {
    int& boneCount = vertex.boneCount;

    if (boneCount < 4) {
        vertex.weights[boneCount] = weight;
        vertex.boneIDs[boneCount] = boneID;

        boneCount++;
    }
}

void AssimpLoader::processBones(std::vector<Vertex>& vertices, aiMesh* mesh) {
    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex) {
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();

        VertexBoneData newBoneInfo;
        newBoneInfo.id = boneIndex;
        newBoneInfo.offsetMatrix = AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);

        boneDataMap[boneName] = newBoneInfo;

        auto weights = mesh->mBones[boneIndex]->mWeights;
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex) {
            int vertexId = weights[weightIndex].mVertexId;
            float weight = weights[weightIndex].mWeight;
            assert(vertexId <= vertices.size());
            addVertexBoneData(vertices[vertexId], boneIndex, weight);
        }
    }
}

//void AssimpLoader::processSkeleton(std::vector<Vertex>& vertices, aiMesh *mesh, aiNode* rootNode) {
//
//
//    for (int i = 0; i < rootNode->mNumChildren; i++)
//    {
//        Bone bone = processBone(vertices, mesh, rootNode->mChildren[i]);
//    }
//
//    Bone2 rootBone;
//
//    bone.name = rootNode->mName.C_Str();
//    bone.parentMatrix = AssimpGLMHelpers::ConvertMatrixToGLMFormat(rootNode->mTransformation);
//
//    for (int i = 0; i < mesh->mNumBones; i++) {
//        aiBone* aiBone = mesh->mBones[i];
//
//        if (aiBone->mName.C_Str() == bone.name) {
//            bone.id = i;
//            bone.offsetMatrix = AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[i]->mOffsetMatrix);
//
//            aiVertexWeight* weights = mesh->mBones[i]->mWeights;
//            for (int j = 0; j < aiBone->mNumWeights; j++) {
//                int vertexId = weights[j].mVertexId;
//                float weight = weights[j].mWeight;
//                addVertexBoneData(vertices[vertexId], 0, weight);
//            }
//
//            break;
//        }
//    }
//}
//
//Bone2 processBone(std::vector<Vertex>& vertices, aiMesh *mesh, aiNode* node) {
//    Bone2 bone;
//
//    bone.name = node->mName.C_Str();
//    bone.parentMatrix = AssimpGLMHelpers::ConvertMatrixToGLMFormat(node->mTransformation);
//
//    for (int i = 0; i < mesh->mNumBones; i++) {
//        aiBone* aiBone = mesh->mBones[i];
//
//        if (aiBone->mName.C_Str() == bone.name) {
//            bone.id = i;
//            bone.offsetMatrix = AssimpGLMHelpers::ConvertMatrixToGLMFormat(mesh->mBones[i]->mOffsetMatrix);
//
//            aiVertexWeight* weights = mesh->mBones[i]->mWeights;
//            for (int j = 0; j < aiBone->mNumWeights; j++) {
//                int vertexId = weights[j].mVertexId;
//                float weight = weights[j].mWeight;
//                addVertexBoneData(vertices[vertexId], i, weight);
//            }
//
//            break;
//        }
//    }
//
//    return bone;
//}

Geometry AssimpLoader::processGeometry(aiMesh *mesh) {
    std::vector<Vertex> vertices = processVertices(mesh);
    std::vector<unsigned int> indices = processIndices(mesh);

    processBones(vertices, mesh);

    return {vertices, indices};
}

Material AssimpLoader::processMaterial(aiMesh *mesh, const aiScene *scene) {
    std::vector<Texture> textures;

    aiMaterial* aiMaterial = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseMaps = processTexturesByType(aiMaterial, aiTextureType_DIFFUSE, Texture::DIFFUSE);
    std::vector<Texture> specularMaps = processTexturesByType(aiMaterial, aiTextureType_SPECULAR, Texture::SPECULAR);

    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

//    Material material(sp);
//    material.addUniform(uniform<Texture>())

    return Material(textures);
}

std::vector<Vertex> AssimpLoader::processVertices(aiMesh *mesh) {
    std::vector<Vertex> vertices;

    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex{};
        for (int j = 0; j < 4; j++) {
            vertex.boneIDs[j] = -1.0f;
        }

        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

        if (mesh->HasNormals()) {
            vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        }

        if (mesh->HasTextureCoords(0)) {
            vertex.texture = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        } else vertex.texture = glm::vec2(0.0f, 0.0f);

        vertex.boneCount = 0;
        vertices.push_back(vertex);
    }

    return vertices;
}

std::vector<unsigned int> AssimpLoader::processIndices(aiMesh *mesh) {
    std::vector<unsigned int> indices;
    for (int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    return indices;
}

std::vector<Texture> AssimpLoader::processTexturesByType(aiMaterial *material, aiTextureType aiType, unsigned int type) {
    std::vector<Texture> textures;
    for (int i = 0; i < material->GetTextureCount(aiType); i++) {
        aiString relativePath;
        material->GetTexture(aiType, i, &relativePath);

        std::string path = directory + '\\' + relativePath.C_Str();

        bool hasTexture = false;
        for (auto & loadedTexture : loadedTextures) {
            if (loadedTexture.path == path) {
                textures.push_back(loadedTexture);
                hasTexture = true;
                break;
            }
        }

        if (!hasTexture) {
            Texture texture = Texture::create(path.c_str(), type);
            textures.push_back(texture);
            loadedTextures.push_back(texture);
        }
    }
    return textures;
}

std::vector<Mesh> AssimpLoader::meshes;
std::string AssimpLoader::directory;
std::vector<Texture> AssimpLoader::loadedTextures;
std::map<std::string, VertexBoneData> AssimpLoader::boneDataMap;
int AssimpLoader::boneCount = 0;