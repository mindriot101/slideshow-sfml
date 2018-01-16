#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace std;

/* Global variables */
const uint32_t WINDOW_WIDTH  = 1280;
const uint32_t WINDOW_HEIGHT = 720;

map<string, sf::Texture> TEXTURES;

void reset_origin(sf::Text &text);
void reset_origin(sf::Sprite &sprite);

struct FontManager {
    map<string, sf::Font> fonts;

    void add(string name, string filename) {
        sf::Font font;
        if (!font.loadFromFile(filename)) {
            cerr << "Cannot load font: " << filename << endl;
            exit(EXIT_FAILURE);
        }
        fonts[name] = font;
    }

    sf::Font get(string name) {
        return fonts[name];
    }
};

struct ImageManager {
    map<string, sf::Sprite> images;

    void add(string name, string filename) {
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            cerr << "Cannot load image: " << filename << endl;
            exit(EXIT_FAILURE);
        }
        TEXTURES[name] = texture;

        sf::Sprite sprite(TEXTURES[name]);
        images[name] = sprite;
    }

    sf::Sprite get(string name) {
        return images[name];
    }
};

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
    string text;
    string font_name;

    /* Image fields */
    string image_name;

    static SlideComponent centered_text(const string &text, const string &font_name) {
        SlideComponent component;
        component.text = text;
        component.component_type = ComponentType::TEXT;
        component.font_name = font_name;
        component.x = WINDOW_WIDTH / 2;
        component.y = WINDOW_HEIGHT / 2;

        return component;
    }

    static SlideComponent centered_image(const string &image_name) {
        SlideComponent component;
        component.image_name = image_name;
        component.component_type = ComponentType::IMAGE;
        component.x = WINDOW_WIDTH / 2;
        component.y = WINDOW_HEIGHT / 2;
        return component;
    }
};

struct Slide {
    vector<SlideComponent> components; 
    sf::Color background_colour = sf::Color(0, 0, 0, 255);

    static Slide simple_centered_text_slide(const string &text, string font_name) {
        Slide slide;

        SlideComponent component = SlideComponent::centered_text(text, font_name);

        slide.components.push_back(component);
        return slide;
    }

    static Slide simple_image_slide(const string &image_name) {
        Slide slide;
        SlideComponent component = SlideComponent::centered_image(image_name);
        slide.components.push_back(component);
        return slide;
    }
};

struct Slideshow {
    vector<Slide> slides;
    uint32_t current_slide = 0;
    FontManager *font_manager;
    ImageManager *image_manager;

    Slideshow(FontManager &font_manager, ImageManager &image_manager) {
        this->font_manager = &font_manager;
        this->image_manager = &image_manager;
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

        window.clear(current->background_colour);

        for (auto component: current->components) {
            switch (component.component_type) {
                case ComponentType::NONE:
                    break;
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
                case ComponentType::IMAGE:
                    {
                        auto sprite = image_manager->get(component.image_name);
                        reset_origin(sprite);
                        sprite.setPosition(component.x, component.y);
                        window.draw(sprite);
                        break;
                    }
            }
        }
    }
};

int main() {
    FontManager font_manager;
    font_manager.add("droid", "run_tree/fonts/DroidSansMono.ttf");

    ImageManager image_manager;
    image_manager.add("cat", "run_tree/images/cat.png");

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");
    window.setVerticalSyncEnabled(true);

    Slideshow slideshow(font_manager, image_manager);
    slideshow.add(Slide::simple_image_slide("cat"));
    slideshow.add(Slide::simple_centered_text_slide("Hello SFML", "droid"));
    slideshow.add(Slide::simple_centered_text_slide("Hello World!", "droid"));
    slideshow.add(Slide::simple_centered_text_slide("Multi\nline\ntext", "droid"));

    slideshow.slides[1].background_colour = sf::Color(255, 0, 0, 255);

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
                    case sf::Keyboard::Space:
                        slideshow.next_slide();
                        break;
                    case sf::Keyboard::P:
                    case sf::Keyboard::BackSpace:
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

void reset_origin(sf::Sprite &sprite) {
    auto bounds = sprite.getGlobalBounds();
    auto width = bounds.width;
    auto height = bounds.height;

    auto half_width = width / 2;
    auto half_height = height / 2;
    sprite.setOrigin(half_width, half_height);
}
