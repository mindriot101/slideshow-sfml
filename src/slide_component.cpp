#include "slide_component.h"

using namespace std;

SlideComponent SlideComponent::centered_text(const string &text,
                                             const string &font_name,
                                             sf::Color font_colour) {
    SlideComponent component;
    component.text = text;
    component.component_type = ComponentType::TEXT;
    component.font_name = font_name;
    component.font_colour = font_colour;
    component.x = 0.5;
    component.y = 0.5;

    return component;
}

SlideComponent SlideComponent::centered_image(const string &image_name) {
    SlideComponent component;
    component.image_name = image_name;
    component.component_type = ComponentType::IMAGE;
    component.x = 0.5;
    component.y = 0.5;
    return component;
}

void SlideComponent::use_shader(const string &shader_name) {
    this->shader_name = shader_name;
    this->custom_shader = true;
}
