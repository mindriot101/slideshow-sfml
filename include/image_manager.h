#ifndef IMAGE_MANAGER_H_
#define IMAGE_MANAGER_H_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

struct ImageManager {
    std::map<std::string, sf::Sprite> images;

    void add(std::string name, std::string filename);
    sf::Sprite get(std::string name);
};

#endif  // IMAGE_MANAGER_H_
