#ifndef SLIDE_COMPONENT_H_
#define SLIDE_COMPONENT_H_

#include <SFML/Graphics.hpp>
#include <string>
#include "globals.h"
#include "option.h"

enum class ComponentType {
    NONE,
    TEXT,
    IMAGE,
};

struct SlideComponent {
    /* General fields */
    float x;
    float y;
    ComponentType component_type = ComponentType::NONE;
    Option<std::string> shader_name = Option<std::string>::None();

    /* Text fields */
    std::string text;
    std::string font_name;
    sf::Color font_colour;

    /* Image fields */
    std::string image_name;

    void use_shader(const std::string &shader_name);

    static SlideComponent centered_text(const std::string &text,
                                        const std::string &font_name,
                                        sf::Color font_colour = WHITE);
    static SlideComponent centered_image(const std::string &image_name);
};

#endif  // SLIDE_COMPONENT_H_
