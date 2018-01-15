#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace std;

const uint32_t WINDOW_WIDTH  = 1280;
const uint32_t WINDOW_HEIGHT = 720;

void reset_origin(sf::Text &text);

struct FontManager {
    map<string, sf::Font> fonts;

    void add(string name, string filename) {
        sf::Font font;
        if (!font.loadFromFile(filename)) {
            exit(EXIT_FAILURE);
        }
        fonts[name] = font;
    }

    sf::Font get(string name) {
        return fonts[name];
    }
};

enum class ComponentType {
    NONE,
    TEXT,
};

struct SlideComponent {
    string text;
    string font_name;
    ComponentType component_type = ComponentType::NONE;
    int x;
    int y;

    static SlideComponent centered_text(const string &text, const string &font_name) {
        SlideComponent component;
        component.text = text;
        component.component_type = ComponentType::TEXT;
        component.font_name = font_name;
        component.x = WINDOW_WIDTH / 2;
        component.y = WINDOW_HEIGHT / 2;

        return component;
    }
};

struct Slide {
    vector<SlideComponent> components; 

    static Slide simple_centered_text_slide(const string &text, string font_name) {
        Slide slide;

        SlideComponent component = SlideComponent::centered_text(text, font_name);

        slide.components.push_back(component);
        return slide;
    }
};

struct Slideshow {
    vector<Slide> slides;
    uint32_t current_slide = 0;
    FontManager *font_manager;

    Slideshow(FontManager &font_manager) {
        this->font_manager = &font_manager;
    }


    void add(const Slide &slide) {
        slides.push_back(slide);
    }

    void next_slide() { current_slide = min(current_slide + 1, uint32_t(slides.size() - 1)); }
    void previous_slide() {
        if (current_slide > 0) {
            current_slide--;
        }
    }

    void render_current_slide(sf::RenderWindow &window) {
        Slide *current = &slides.at(current_slide);

        for (auto component: current->components) {
            switch (component.component_type) {
                case ComponentType::TEXT:
                    {
                        auto text_content = component.text;
                        auto font = font_manager->get(component.font_name);

                        sf::Text text(text_content, font, 50);
                        reset_origin(text);
                        text.setPosition(component.x, component.y);
                        window.draw(text);
                    break;
                    }
                default:
                    {
                    break;
                    }
            }
        }
    }
};

int main() {
    FontManager font_manager;
    font_manager.add("droid", "run_tree/fonts/DroidSansMono.ttf");

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");
    window.setVerticalSyncEnabled(true);

    Slideshow slideshow(font_manager);
    slideshow.add(Slide::simple_centered_text_slide("Hello SFML", "droid"));
    slideshow.add(Slide::simple_centered_text_slide("Hello World!", "droid"));
    slideshow.add(Slide::simple_centered_text_slide("Multi\nline\ntext", "droid"));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::Q:
                        window.close();
                        break;
                    case sf::Keyboard::N:
                        slideshow.next_slide();
                        break;
                    case sf::Keyboard::P:
                        slideshow.previous_slide();
                        break;
                    default:
                        break;
                }
            }
        }

        window.clear();

        slideshow.render_current_slide(window);

        window.display();
    }

    return EXIT_SUCCESS;
}



void reset_origin(sf::Text &text) {
    auto bounds = text.getGlobalBounds();
    auto width = bounds.width;
    auto height = bounds.height;

    auto half_width = width / 2;
    auto half_height = height / 2;
    text.setOrigin(half_width, half_height);
}
