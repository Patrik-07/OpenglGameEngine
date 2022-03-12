#include "AssimpLoader.h"

#include "../Opengl/Texture.h"
#include "../Model/Mesh.h"

Model AssimpLoader::load(const std::string& modelPath, ShaderProgram& shaderProgram) {
    directory = "";
    loadedTextures.clear();

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
    }

    directory = modelPath.substr(0, modelPath.find_last_of('\\'));
    processNode(scene->mRootNode, scene);

    sp = shaderProgram;
    return {meshes, sp};
}

void AssimpLoader::processNode(aiNode *node, const aiScene *scene) {
    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];

        auto meshFuture = std::async(std::launch::deferred, processMesh, aiMesh, scene);
        Mesh mesh = meshFuture.get();

        meshes.push_back(mesh);
    }
    for (int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh AssimpLoader::processMesh(aiMesh *mesh, const aiScene *scene) {
    auto geometryFuture = std::async(std::launch::deferred, processGeometry, mesh);
    auto materialFuture = std::async(std::launch::deferred, processMaterial, mesh, scene);

    Geometry geometry = geometryFuture.get();
    Material material = materialFuture.get();

    return {geometry, material};
}

Geometry AssimpLoader::processGeometry(aiMesh *mesh) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    auto verticesFuture = std::async(std::launch::deferred, processVertices, mesh);
    auto indicesFuture = std::async(std::launch::deferred, processIndices, mesh);

    vertices = verticesFuture.get();
    indices = indicesFuture.get();

    return {vertices, indices};
}

Material AssimpLoader::processMaterial(aiMesh *mesh, const aiScene *scene) {
    std::vector<Texture> textures;

    aiMaterial* aiMaterial = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseMaps = processTexturesByType(aiMaterial, aiTextureType_DIFFUSE, Texture::DIFFUSE);
    std::vector<Texture> specularMaps = processTexturesByType(aiMaterial, aiTextureType_SPECULAR, Texture::SPECULAR);

    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    Material material(sp);
    material.addUniform(Uniform<Texture>())

    return Material(textures);
}

std::vector<Vertex> AssimpLoader::processVertices(aiMesh *mesh) {
    std::vector<Vertex> vertices;
    for (int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex{};

        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);

        if (mesh->HasNormals()) {
            vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        }

        if (mesh->HasTextureCoords(0)) {
            vertex.texture = glm::vec2(mesh->mTextureCoords[0][i].x, 1 - mesh->mTextureCoords[0][i].y);
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