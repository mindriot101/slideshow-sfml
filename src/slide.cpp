#include "slide.h"

using namespace std;

Slide Slide::simple_centered_text_slide(const string &text, string font_name, sf::Color font_colour, sf::Color slide_background_colour) {
    Slide slide;
    slide.background_colour = slide_background_colour;

    SlideComponent component = SlideComponent::centered_text(text, font_name, font_colour);

    slide.components.push_back(component);
    return slide;
}

Slide Slide::simple_image_slide(const string &image_name, sf::Color background_colour) {
    Slide slide;

    slide.background_colour = background_colour;
    SlideComponent component = SlideComponent::centered_image(image_name);
    slide.components.push_back(component);
    slide.components.push_back(SlideComponent::centered_text("CAT!", "droid", BLACK));
    return slide;
}
