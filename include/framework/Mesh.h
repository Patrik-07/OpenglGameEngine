#pragma once

class Mesh {
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    // Texture texture;
    bool isSmooth;

    unsigned int VAO = 0;
public:
    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<int>& indices,
         bool isSmooth
    ) {
        this->vertices = vertices;
        this->indices = indices;
        this->isSmooth = isSmooth;

        glGenVertexArrays(1, &VAO);

        unsigned int VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

//        for (Vertex va : vertices) {
//            float px = va.getPosition().x;
//            float py = va.getPosition().y;
//            float pz = va.getPosition().z;
//
//            float nx = va.getNormal().x;
//            float ny = va.getNormal().y;
//            float nz = va.getNormal().z;
//
//            float tx = va.getTexture().x;
//            float ty = va.getTexture().y;
//
//            std::cout << "---------------\n";
//            std::cout << px << ", " << py << ", " << pz << std::endl;
//            std::cout << nx << ", " << ny << ", " << nz << std::endl;
//            std::cout << tx << ", " << ty << std::endl;
//        }

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)20);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3) + 20));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((2 * sizeof(glm::vec3)) + 16));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_DYNAMIC_DRAW);

        glBindVertexArray(0);
    }

    void free() {
        std::vector<Vertex> v;
        vertices.swap(v);
    }

    std::vector<Vertex> getVertices() {
        return vertices;
    }

    std::vector<int> getIndices() {
        return indices;
    }

    void draw() {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
};

