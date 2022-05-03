#pragma once

#define STB_IMAGE_STATIC // Should remove
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <iostream>

class Image {
    int width, height;
    int colorDepth;
    unsigned char* data;
public:
    static Image load(const char* imagePath) {
        Image i(imagePath);
        return i;
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

private:
    Image(const std::string& imagePath) {
        data = stbi_load(imagePath.c_str(), &width, &height, &colorDepth, 0);
        if (data == nullptr) {
            printf("Couldn't load image");
            exit(-1);
        }
    }
};