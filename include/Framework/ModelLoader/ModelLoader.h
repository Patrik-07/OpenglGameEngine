#pragma once

#include <iostream>
#include <future>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Framework/Model/Model.h"

class ModelLoader {
    static std::vector<Mesh> meshes;
    static std::string directory;
    static std::vector<Texture> loadedTextures;

public:
    static Model load(const std::string& modelPath);

private:
    static void processNode(aiNode* node, const aiScene* scene);
    static Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    static Geometry processGeometry(aiMesh* mesh);
    static Material processMaterial(aiMesh* mesh, const aiScene* scene);
    static std::vector<Vertex> processVertices(aiMesh* mesh);
    static std::vector<unsigned int> processIndices(aiMesh* mesh);
    static std::vector<Texture> processTexturesByType(aiMaterial* material, aiTextureType aiType, unsigned int type);
};