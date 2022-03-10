#pragma once

enum Direction {
    FORTH, BACK, RIGHT, LEFT
};

class Camera {
    glm::vec3 target;
    glm::vec3 up;

    float pitch, yaw;

    IScene& scene;
public:
    glm::vec3 position;
    Camera(IScene& scene) : scene(scene) {
        position = glm::vec3(15.0f, 10.0f, 15.0f);
        target = glm::vec3(-0.55f, -0.43f, -0.7f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);

        yaw = -127.5f;
        pitch = -25.5f;
    }

    void move(Direction direction, float speed) {
        switch (direction) {
            case FORTH: position += speed * target; break;
            case BACK: position -= speed * target; break;
            case RIGHT: position += glm::normalize(glm::cross(target, up)) * speed; break;
            case LEFT: position -= glm::normalize(glm::cross(target, up)) * speed; break;
        }
        scene.refresh();
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
        scene.refresh();
    }

    void update() {

    }

    glm::vec3 getPosition() const {
        return position;
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(position, position + target, up);
    }

    glm::mat4 getProjectionMatrix() const {
        return glm::perspective(glm::radians(45.0f), (float)scene.width / (float)scene.height, 0.1f, 1000.0f);
    }
};