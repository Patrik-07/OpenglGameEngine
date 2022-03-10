#include "Material.h"

Material::Material(std::vector<Texture> textures) {
    this->textures = std::move(textures);
}