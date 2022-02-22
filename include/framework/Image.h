#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

class Image {
    int width, height;
    int colorDepth;
    unsigned char* data;
public:
    explicit Image(const char* imagePath) {
        data = stbi_load(imagePath, &width, &height, &colorDepth, 0);
        if (data == nullptr) {
            printf("Couldn't load image");
            exit(-1);
        }
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    int getColorDepth() const {
        return colorDepth;
    }

    unsigned char* getData() {
        return data;
    }

    void free() {
        stbi_image_free(data);
    }
};