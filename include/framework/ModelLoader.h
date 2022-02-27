#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ModelLoader {
    static std::vector<Mesh> meshes;
    static std::string directory;
    static std::vector<Texture> loadedTextures;
public:
    static Model load(const std::string& modelPath) {
        meshes.clear();
        directory = "";
        loadedTextures.clear();

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(modelPath, aiProcessPreset_TargetRealtime_Fast);

        directory = modelPath.substr(0, modelPath.find_last_of('\\'));
        processNode(scene->mRootNode, scene);

        return {meshes, directory};
    }

private:
    static void processNode(aiNode* node, const aiScene* scene) {
        for (int i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }
        for (int i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    static Mesh processMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        // separate
        for (int i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex{};

            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);;

            if (mesh->HasNormals()) {
                vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            }

            if (mesh->HasTextureCoords(0)) {
                vertex.texture = glm::vec2(mesh->mTextureCoords[0][i].x, 1 - mesh->mTextureCoords[0][i].y);
            } else vertex.texture = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }

        // separate
        for (int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<glm::vec3> aa;
        glm::vec3 color(0.0f, 0.0f, 0.0f);
        aiColor3D diffuse(0.0f, 0.0f, 0.0f);
        if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse))
            color = glm::vec3(diffuse.r, diffuse.g, diffuse.b);
        aa.push_back(color);

        ai_int illumModel;
        material->Get(AI_MATKEY_SHADING_MODEL, illumModel);

        std::vector<Texture> diffuseMaps = processTexturesByType(material, aiTextureType_DIFFUSE, DIFFUSE);
        std::vector<Texture> specularMaps = processTexturesByType(material, aiTextureType_SPECULAR, SPECULAR);

        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//        std::vector<Texture> specularMaps = processTexturesByType(material, aiTextureType_SPECULAR, "specularMap");
//        std::vector<Texture> ambientMaps = processTexturesByType(material, aiTextureType_AMBIENT, "ambientMap");

        return {vertices, indices, textures};
    }

    static std::vector<Texture> processTexturesByType(aiMaterial* material, aiTextureType aiType, TextureType type) {
        std::vector<Texture> textures;
        for (int i = 0; i < material->GetTextureCount(aiType); i++) {
            aiString relativePath;
            material->GetTexture(aiType, i, &relativePath);

            std::string path = directory + '\\' + relativePath.C_Str();

            bool hasTexture = false;
            for (int j = 0; j < loadedTextures.size(); j++) {
                if (loadedTextures[j].getPath() == path) {
                    textures.push_back(loadedTextures[j]);
                    hasTexture = true;
                    break;
                }
            }

            if (!hasTexture) {
                Texture texture(path, type);
                textures.push_back(texture);
                loadedTextures.push_back(texture);
            }
        }
        return textures;
    }
};
std::vector<Mesh> ModelLoader::meshes;
std::string ModelLoader::directory;
std::vector<Texture> ModelLoader::loadedTextures;