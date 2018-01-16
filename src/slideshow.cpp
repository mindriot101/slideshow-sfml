#include "slideshow.h"

using namespace std;

namespace {
    void reset_origin(sf::Text &text) {
        auto bounds = text.getGlobalBounds();
        auto width = bounds.width;
        auto height = bounds.height;

        auto half_width = width / 2;
        auto half_height = height / 2;
        text.setOrigin(half_width, half_height);
    }

    void reset_origin(sf::Sprite &sprite) {
        auto bounds = sprite.getGlobalBounds();
        auto width = bounds.width;
        auto height = bounds.height;

        auto half_width = width / 2;
        auto half_height = height / 2;
        sprite.setOrigin(half_width, half_height);
    }
}

Slideshow::Slideshow(FontManager &font_manager, ImageManager &image_manager) {
    this->font_manager = &font_manager;
    this->image_manager = &image_manager;
}

void Slideshow::add(const Slide &slide) {
    slides.push_back(slide);
}

void Slideshow::render_current_slide(sf::RenderWindow *window) {
    Slide *current = &slides.at(current_slide);

    window->clear(current->background_colour);

    for (auto component: current->components) {
        switch (component.component_type) {
            case ComponentType::NONE:
                break;
            case ComponentType::TEXT:
                {
                    auto text_content = component.text;
                    auto font = font_manager->get(component.font_name);

                    sf::Text text(text_content, font, 84);
                    reset_origin(text);
                    text.setPosition(component.x, component.y);
                    text.setFillColor(component.font_colour);
                    window->draw(text);
                    break;
                }
            case ComponentType::IMAGE:
                {
                    auto sprite = image_manager->get(component.image_name);
                    reset_origin(sprite);
                    sprite.setPosition(component.x, component.y);
                    window->draw(sprite);
                    break;
                }
        }
    }
}

void Slideshow::recenter_content() {
}

bool Slideshow::is_empty() const {
    return slides.size() == 0;
}
