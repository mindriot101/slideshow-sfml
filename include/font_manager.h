#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

struct FontManager {
    std::map<std::string, sf::Font> fonts;

    void add(std::string name, std::string filename);
    sf::Font get(std::string name);
};

#endif // FONT_MANAGER_H_
