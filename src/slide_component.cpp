#include "slide_component.h"

using namespace std;

SlideComponent SlideComponent::centered_text(const string &text, const string &font_name, sf::Color font_colour) {
    SlideComponent component;
    component.text = text;
    component.component_type = ComponentType::TEXT;
    component.font_name = font_name;
    component.font_colour = font_colour;
    component.x = WINDOW_WIDTH / 2;
    component.y = WINDOW_HEIGHT / 2;

    return component;
}

SlideComponent SlideComponent::centered_image(const string &image_name) {
    SlideComponent component;
    component.image_name = image_name;
    component.component_type = ComponentType::IMAGE;
    component.x = WINDOW_WIDTH / 2;
    component.y = WINDOW_HEIGHT / 2;
    return component;
}
