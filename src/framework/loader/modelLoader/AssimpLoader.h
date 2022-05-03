#pragma once

#include <iostream>
#include <future>
#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "ModelLoader.h"
#include "../../model/VertexBoneData.h"
#include "../../animation/Animation.h"

class Model;
class Mesh;
class Geometry;
class Material;
class Vertex;
class Texture;

class AssimpLoader : public ModelLoader {
    static ShaderProgram sp;
    static std::vector<Mesh> meshes;
    static std::string directory;
    static std::vector<Texture> loadedTextures;
    static std::map<std::string, VertexBoneData> boneDataMap;
    static int boneCount;

public:
    Model load(const std::string& modelPath) override;

private:
    static void processNode(aiNode* node, const aiScene* scene);
    static Mesh processMesh(aiMesh* mesh, const aiScene* scene);

    static Geometry processGeometry(aiMesh* mesh);
    static Material processMaterial(aiMesh* mesh, const aiScene* scene);

    static std::vector<Vertex> processVertices(aiMesh* mesh);
    static std::vector<unsigned int> processIndices(aiMesh* mesh);
    static std::vector<Texture> processTexturesByType(aiMaterial* material, aiTextureType aiType, unsigned int type);

    static void processBones(std::vector<Vertex>& vertices, aiMesh* mesh);
//    static void processSkeleton(std::vector<Vertex>& vertices, aiMesh *mesh, aiNode* rootNode);
//    static Bone2 processBone(std::vector<Vertex>& vertices, aiMesh *mesh, aiNode* node);
};