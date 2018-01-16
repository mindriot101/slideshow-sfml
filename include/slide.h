#ifndef SLIDE_H_
#define SLIDE_H_

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "slide_component.h"

struct Slide {
    std::vector<SlideComponent> components; 
    sf::Color background_colour = sf::Color(0, 0, 0, 255);

    static Slide simple_centered_text_slide(const std::string &text, std::string font_name, sf::Color font_colour=WHITE);
    static Slide simple_image_slide(const std::string &image_name);
};

#endif // SLIDE_H_
