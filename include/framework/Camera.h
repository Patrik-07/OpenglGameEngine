#pragma once

enum Direction {
    FORTH, BACK, RIGHT, LEFT
};

class Camera {
    glm::vec3 target;
    glm::vec3 up;

    float pitch, yaw;

    IScene* scene;
public:
    glm::vec3 position;
    Camera(IScene* scene) : scene(scene) {
        position = glm::vec3(0.0f, 2.0f, 5.0f);
        target = glm::vec3(0.0f, 0.0f, -1.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);

        yaw = -90.0f;
        pitch = 0.0f;
    }

    void move(Direction direction, float speed) {
        switch (direction) {
            case FORTH: position += speed * target; break;
            case BACK: position -= speed * target; break;
            case RIGHT: position += glm::normalize(glm::cross(target, up)) * speed; break;
            case LEFT: position -= glm::normalize(glm::cross(target, up)) * speed; break;
        }
        scene->refresh();
    }

    void refresh() {
        scene->refresh();
    }

    void rotate(float x, float y) {
        pitch += y;
        yaw += x;

        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        target.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        target.y = sin(glm::radians(pitch));
        target.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        target = glm::normalize(target);
        scene->refresh();
    }

    glm::vec3 getPosition() {
        return position;
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, position + target, up);
    }

    glm::mat4 getProjectionMatrix() {
        return glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 1000.0f);
    }
};