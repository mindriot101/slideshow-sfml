#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <map>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "globals.h"
#include "font_manager.h"
#include "image_manager.h"
#include "slide_component.h"
#include "slide.h"
#include "slideshow.h"
#include "main_window.h"

using namespace std;

/* Have to hold the textures at constant points in memory
 * or else we lose the texture content when making sprites */
std::map<std::string, sf::Texture> TEXTURES;

int main() {
    FontManager font_manager;
    font_manager.add("droid", "run_tree/fonts/DroidSansMono.ttf");

    ImageManager image_manager;
    image_manager.add("cat", "run_tree/images/cat.png");

    MainWindow window;

    Slideshow slideshow(font_manager, image_manager);
    slideshow.add(Slide::simple_centered_text_slide("Hello SFML", "droid", WHITE, GREEN));
    slideshow.add(Slide::simple_image_slide("cat", RED));
    slideshow.add(Slide::simple_centered_text_slide("Hello World!", "droid", GREEN, WHITE));
    slideshow.add(Slide::simple_centered_text_slide("Multi\nline\ntext", "droid"));

    while (window.window->isOpen()) {
        sf::Event event;
        while (window.window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.window->close();
            } else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::Q:
                        window.window->close();
                        break;
                    case sf::Keyboard::N:
                    case sf::Keyboard::Space:
                        slideshow.next_slide();
                        break;
                    case sf::Keyboard::P:
                    case sf::Keyboard::BackSpace:
                        slideshow.previous_slide();
                        break;
                    case sf::Keyboard::F:
                        window.toggle_fullscreen();
                        slideshow.recenter_content();
                        break;
                    default:
                        break;
                }
            }
        }

        slideshow.render_current_slide(window.window);
        window.window->display();
    }

    return EXIT_SUCCESS;
}



