#include "game/Textures.h"

std::string TexturesMap::getTexture(std::string textureName, std::string textureLevel) {
    return textures[textureLevel][textureName];
}

std::map<std::string, std::map<std::string, std::string>> TexturesMap::getTextures() {
    return textures;
}