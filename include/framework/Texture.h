#pragma once

class Texture {
    unsigned int ID = 0;
public:
    explicit Texture(const char* imagePath) {
        Image image(imagePath);

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//        int width, height, nrChannels;
//        unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.getWidth(), image.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.getData());
        glGenerateMipmap(GL_TEXTURE_2D);

//        stbi_image_free(data);
        image.free();
    }

    unsigned int getID() const {
        return ID;
    }

    ~Texture() {
        glDeleteTextures(1, &ID);
    }
};