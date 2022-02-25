#pragma once

class Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    unsigned int VAO = 0;
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        glGenVertexArrays(1, &VAO);

        unsigned int VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((2 * sizeof(glm::vec3))));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_DYNAMIC_DRAW);

        glBindVertexArray(0);
    }

    std::vector<Vertex> getVertices() {
        return vertices;
    }

    std::vector<unsigned int> getIndices() {
        return indices;
    }

    void draw(ShaderProgram& shaderProgram) {
        for (int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            TextureType type = textures[i].getType();

            int location = glGetUniformLocation(textures[i].getID(), "material.diffuseMap");
            glUniform1i(location, i);
            glBindTexture(GL_TEXTURE_2D, textures[i].getID());
//            switch (type) {
//                case DIFFUSE:
//                    shaderProgram.setUniform("material.diffuseMap", textures[i], i);
//                    break;
//                case SPECULAR:
//                case AMBIENT:
//                default:
//                    break;
//            }
        }
        glActiveTexture(GL_TEXTURE0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};

