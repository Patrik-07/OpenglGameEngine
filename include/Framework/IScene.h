#pragma once

class IScene {
public:
    int& width;
    int& height;
    virtual void refresh() = 0;
    IScene(int& width, int& height) : width(width), height(height) {}
};