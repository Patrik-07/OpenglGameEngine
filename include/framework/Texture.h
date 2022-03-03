#pragma once

enum TextureType {
    DIFFUSE,
    SPECULAR,
    AMBIENT
};

class Texture {
    unsigned int ID = 0;
    TextureType type;
    std::string path;
public:
    explicit Texture(const std::string& imagePath, TextureType type) {
        Image image(imagePath);

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        GLint format;
        unsigned int colorDepth = image.getColorDepth();
        if (colorDepth == 1) {
            format = GL_RED;
        } else if (colorDepth == 3) {
            format = GL_RGB;
        } else if (colorDepth == 4) {
            format = GL_RGBA;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, image.getWidth(), image.getHeight(), 0, format, GL_UNSIGNED_BYTE, image.getData());
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        this->type = type;
        this->path = imagePath;
        image.free();
    }

    unsigned int getID() const {
        return ID;
    }

    std::string getPath() const {
        return path;
    }

    TextureType getType() const {
        return type;
    }
};