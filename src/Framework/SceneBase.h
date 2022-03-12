#pragma once

class SceneBase {
public:
    int& width;
    int& height;
    virtual void refresh() = 0;
    SceneBase(int& width, int& height) : width(width), height(height) {}
};