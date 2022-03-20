#pragma once

#include "../Scene/Camera.h"
#include "SDL2/SDL_scancode.h"
#include "SDL2/SDL_keyboard.h"
#include "SDL2/SDL_mouse.h"

class CameraHandler {
    Camera& camera;

    float boost;
    float movementSpeed;

    float prevX, prevY;
    float isFirst;

public:
    CameraHandler(Camera& camera) : camera(camera) {
        boost = 0.0f;
        movementSpeed = 0.05f;

        prevX = prevY = 0.0f;
        isFirst = false;
    }

    void process(float deltaTime) {
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_W]) {
            camera.move(FORTH, movementSpeed + boost);
        }
        if (state[SDL_SCANCODE_A]) {
            camera.move(LEFT, movementSpeed + boost);
        }
        if (state[SDL_SCANCODE_S]) {
            camera.move(BACK, movementSpeed + boost);
        }
        if (state[SDL_SCANCODE_D]) {
            camera.move(RIGHT, movementSpeed + boost);
        }
        if (state[SDL_SCANCODE_E]) {
            camera.position.y += ((4.0f * deltaTime) + boost);
        }
        if (state[SDL_SCANCODE_Q]) {
            camera.position.y -= ((4.0f * deltaTime) + boost);
        }
        if (state[SDL_SCANCODE_LSHIFT]) {
            if (movementSpeed + boost < 0.5) {
                boost += 0.01f;
            }
        } else boost = 0.0f;

        int x, y;
        const Uint32 mouseState = SDL_GetMouseState(&x, &y);
        if (mouseState == SDL_BUTTON_MIDDLE) {
            if (isFirst) {
                prevX = x;
                prevY = y;
                isFirst = false;
            }

            float offsetX = x - prevX;
            float offsetY = prevY - y;

            float mouseSensitivity = 5.0f * deltaTime;
            offsetX *= mouseSensitivity;
            offsetY *= mouseSensitivity;

            camera.rotate(offsetX, offsetY);
            prevX = x;
            prevY = y;

        } else isFirst = true;
    }
};