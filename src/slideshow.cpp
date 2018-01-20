#include "slideshow.h"
#include <iostream>
#include <sstream>
#include "presenter_time.h"

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

string colour_to_string(const sf::Color &colour) {
    stringstream ss;
    ss << int(colour.r) << "," << int(colour.g) << "," << int(colour.g);
    return ss.str();
}

void print(const SlideComponent &c, int no) {
    cout << "  - Component: " << no << endl;

    if (c.shader_name) {
        cout << "    - Shader name: " << c.shader_name.value << endl;
    } else {
        cout << "    - No shader" << endl;
    }

    switch (c.component_type) {
        case ComponentType::NONE:
            break;
        case ComponentType::TEXT:
            cout << "    - Text: " << c.text << endl;
            cout << "    - Font: " << c.font_name << endl;
            cout << "    - Font colour: " << colour_to_string(c.font_colour)
                 << endl;
            break;
        case ComponentType::IMAGE:
            cout << "    - Image name: " << c.image_name << endl;
            break;
    }
}

}  // namespace

Slideshow::Slideshow(FontManager &font_manager, ImageManager &image_manager,
                     ShaderManager &shader_manager) {
    this->font_manager = &font_manager;
    this->image_manager = &image_manager;
    this->shader_manager = &shader_manager;
}

void Slideshow::add(const Slide &slide) { slides.push_back(slide); }

void Slideshow::render_current_slide(const unique_ptr<MainWindow> &main_window,
                                     const Time &time) {
    auto res = main_window->window->getSize();

    auto scaling = main_window->scaling_factor;
    Slide *current = &slides.at(current_slide);

    main_window->window->clear(current->background_colour);

    for (auto component : current->components) {
        switch (component.component_type) {
            case ComponentType::NONE:
                break;
            case ComponentType::TEXT: {
                auto text_content = component.text;
                auto font = font_manager->get(component.font_name);

                sf::Text text(text_content, font, 84 * scaling);
                reset_origin(text);
                text.setPosition((1.0 - component.x) * res.x,
                                 (1.0 - component.y) * res.y);
                text.setFillColor(component.font_colour);
                if (component.shader_name) {
                    auto shader =
                        shader_manager->get(component.shader_name.value);
                    shader->setUniform("t", time.total);
                    main_window->window->draw(text, shader.get());
                } else {
                    main_window->window->draw(text);
                }
                break;
            }
            case ComponentType::IMAGE: {
                auto sprite = image_manager->get(component.image_name);
                reset_origin(sprite);
                sprite.setPosition(component.x * res.x, component.y * res.y);
                sprite.setScale(scaling, scaling);
                if (component.shader_name) {
                    auto shader =
                        shader_manager->get(component.shader_name.value);
                    shader->setUniform("t", time.total);
                    main_window->window->draw(sprite, shader.get());
                } else {
                    main_window->window->draw(sprite);
                }
                break;
            }
        }
    }
}

void Slideshow::recenter_content() {}

bool Slideshow::is_empty() const { return slides.size() == 0; }

Slide *Slideshow::last() {
    size_t len = slides.size();
    if (len > 0) {
        return &slides[len - 1];
    }

    return nullptr;
}

void Slideshow::print_current(int current_slide) {
    cout << "Slide " << current_slide << ":" << endl;
    Slide *current = &slides[current_slide];

    auto c = current->background_colour;

    cout << "  - background colour: " << colour_to_string(c) << endl;

    int component_no = 0;
    for (auto component : current->components) {
        print(component, component_no);
        component_no++;
    }
    cout << endl;
}

void Slideshow::next_slide() {
    current_slide = std::min(current_slide + 1, uint32_t(slides.size() - 1));
    print_current(current_slide);
}

void Slideshow::previous_slide() {
    if (current_slide > 0) {
        current_slide--;
    }
    print_current(current_slide);
}
