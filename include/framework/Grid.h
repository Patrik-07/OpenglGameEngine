#pragma once

#include <set>

class Grid {
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
    unsigned int VBO, EBO, VAO;
    int dim;
    float scaleValue;
public:
    Grid(int n) {
        setup(n);
    }

    void setup(int n) {
        if (dim != n) {
            dim = n;
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);

            vertices.clear();
            indices.clear();

            scaleValue = 1.0f;
            int k = 0;
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= n; j++) {
                    glm::vec3 v(((float) i / ((float) n / 2)) - 1.0f, 0.0f, ((float) j / ((float) n / 2)) - 1.0f);
                    vertices.emplace_back(v);

                    int right = k + n + 1;
                    int bottom = k + 1;

                    if (k < n * (n + 1)) {
                        indices.push_back(k);
                        indices.push_back(right);
                    }
                    if (bottom % (n + 1) != 0) {
                        indices.push_back(k);
                        indices.push_back(bottom);
                    }
                    k++;
                }
            }

            glGenVertexArrays(1, &VAO);

            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            glBindVertexArray(0);
        }
    }

    void reset(int n) {
        setup(n);
    }

    void draw() const {
        glEnable(GL_DEPTH);
        glBindVertexArray(VAO);
        glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
};