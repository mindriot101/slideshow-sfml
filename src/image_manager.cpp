#include "image_manager.h"
#include <iostream>

using namespace std;

extern std::map<std::string, sf::Texture> TEXTURES;

void ImageManager::add(string name, string filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        cerr << "Cannot load image: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    TEXTURES[name] = texture;

    sf::Sprite sprite(TEXTURES[name]);
    images[name] = sprite;
}

sf::Sprite ImageManager::get(string name) {
    return images[name];
}
