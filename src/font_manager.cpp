#include "font_manager.h"
#include <iostream>

using namespace std;

void FontManager::add(string name, string filename) {
    sf::Font font;
    if (!font.loadFromFile(filename)) {
        cerr << "Cannot load font: " << filename << endl;
        exit(EXIT_FAILURE);
    }
    fonts[name] = font;
}

sf::Font FontManager::get(string name) {
    return fonts[name];
}
