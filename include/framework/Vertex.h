#pragma once

class Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture;
public:
    Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texture) {
        this->position = position;
        this->normal = normal;
        this->texture = texture;
    }

    glm::vec3 getPosition() {
        return position;
    }

    glm::vec3 getNormal() {
        return normal;
    }

    glm::vec2 getTexture() {
        return texture;
    }
};