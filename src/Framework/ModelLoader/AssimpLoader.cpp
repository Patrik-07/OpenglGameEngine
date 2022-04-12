#include "AssimpLoader.h"

#include "../Opengl/Texture/Texture.h"
#include "../Model/Mesh.h"
#include "../Model/VertexBoneData.h"

Model AssimpLoader::load(const std::string& modelPath) {
    directory = "";
    loadedTextures.clear();

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

    directory = modelPath.substr(0, modelPath.find_last_of('\\'));

    aiNode *node = scene->mRootNode;

    processNode(node, scene);

    return {meshes, boneDataMap};
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

Geometry AssimpLoader::processGeometry(aiMesh *mesh) {
    std::vector<Vertex> vertices = processVertices(mesh);
    std::vector<unsigned int> indices = processIndices(mesh);

    // extract into a new function: processBones
    if (mesh->HasBones()) {
        for (int i = 0; i < mesh->mNumBones; i++) {
            int boneID = -1;
            std::string boneName = mesh->mBones[i]->mName.C_Str();
            if (boneDataMap.find(boneName) == boneDataMap.end()) {
                aiMatrix4x4 m = mesh->mBones[i]->mOffsetMatrix;
                glm::mat4 offsetMatrix(
                    m.a1, m.a2, m.a3, m.a4,
                    m.b1, m.b2, m.b3, m.b4,
                    m.c1, m.c2, m.c3, m.c4,
                    m.d1, m.d2, m.d3, m.d4
                );
                boneID = boneCount;
                boneDataMap[boneName] = VertexBoneData{boneID, offsetMatrix};
                boneCount++;
            } else {
                boneID = boneDataMap[boneName].vertexID;
            }

            auto weights = mesh->mBones[i]->mWeights;
            int numWeights = mesh->mBones[i]->mNumWeights;

            for (int j = 0; j < numWeights; j++) {
                unsigned int vertexID = weights[j].mVertexId;
                float weight = weights[j].mWeight;

                Vertex& v = vertices[vertexID];
                for (int k = 0; k < 4; k++) {
                    if (v.boneIDs[k] < 0) {
                        v.boneIDs[k] = boneID;
                        v.weights[k] = weight;
                    }
                }
            }
        }
    }

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
//    material.addUniform(Uniform<Texture>())

    return Material(textures);
}

std::vector<Vertex> AssimpLoader::processVertices(aiMesh *mesh) {
    std::vector<Vertex> vertices;

    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex{};
        for (int j = 0; j < 4; j++) {
            vertex.boneIDs[j] = -1;
        }

        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

        if (mesh->HasNormals()) {
            vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        }

        if (mesh->HasTextureCoords(0)) {
            vertex.texture = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        } else vertex.texture = glm::vec2(0.0f, 0.0f);

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