#pragma once

#include <chrono>
#include <iostream>

class Timer {
    std::chrono::time_point<std::chrono::system_clock> timeAtLastFrame = std::chrono::system_clock::now();
public:
    Timer() {
        reStart();
    }

    void reStart() {
        timeAtLastFrame = std::chrono::system_clock::now();
    }

    float getDeltaTime() {
        std::chrono::time_point<std::chrono::system_clock> timeAtThisFrame = std::chrono::system_clock::now();
        float dt = (std::chrono::duration<float>(timeAtThisFrame - timeAtLastFrame)).count();
        timeAtLastFrame = timeAtThisFrame;

        return dt;
    }
};