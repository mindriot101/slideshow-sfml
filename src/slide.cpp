#include "slide.h"

using namespace std;

Slide Slide::simple_centered_text_slide(const string &text, string font_name, sf::Color font_colour) {
    Slide slide;

    SlideComponent component = SlideComponent::centered_text(text, font_name, font_colour);

    slide.components.push_back(component);
    return slide;
}

Slide Slide::simple_image_slide(const string &image_name) {
    Slide slide;
    SlideComponent component = SlideComponent::centered_image(image_name);
    slide.components.push_back(component);
    return slide;
}
