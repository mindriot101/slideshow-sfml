#ifndef SLIDE_COMPONENT_H_
#define SLIDE_COMPONENT_H_

#include <string>
#include <SFML/Graphics.hpp>
#include "globals.h"

enum class ComponentType {
    NONE,
    TEXT,
    IMAGE,
};

struct SlideComponent {
    /* General fields */
    int x;
    int y;
    ComponentType component_type = ComponentType::NONE;

    /* Text fields */
    std::string text;
    std::string font_name;
    sf::Color font_colour;

    /* Image fields */
    std::string image_name;

    static SlideComponent centered_text(const std::string &text, const std::string &font_name, sf::Color font_colour=WHITE); 
    static SlideComponent centered_image(const std::string &image_name); 
};

#endif // SLIDE_COMPONENT_H_
