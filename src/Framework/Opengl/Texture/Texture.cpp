#include "Texture.h"

Texture::Texture(const char *imagePath, unsigned int type) {
    Image image = Image::load(imagePath);

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    GLenum format = 0;
    unsigned int colorDepth = image.getColorDepth();
    if (colorDepth == 1) {
        format = GL_RED;
    } else if (colorDepth == 2) {
        format = GL_RG;
    } else if (colorDepth == 3) {
        format = GL_RGB;
    } else if (colorDepth == 4) {
        format = GL_RGBA;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, image.getWidth(), image.getHeight(), 0, format, GL_UNSIGNED_BYTE, image.getData());
    glGenerateMipmap(GL_TEXTURE_2D);

    this->type = type;
    this->path = imagePath;
    image.free();
}

Texture Texture::create(const char *imagePath, unsigned int type) {
    return Texture(imagePath, type);
}