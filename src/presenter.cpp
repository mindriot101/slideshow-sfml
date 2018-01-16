#include "presenter.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "slideshow.h"

using namespace std;

Presenter::Presenter() {
    font_manager.add("droid", "run_tree/fonts/DroidSansMono.ttf");
    image_manager.add("cat", "run_tree/images/cat.png");

    slideshow = new Slideshow(font_manager, image_manager);
    /* setup_test_slideshow(); */
}

Presenter::~Presenter() {
    if (slideshow != nullptr) {
        delete slideshow;
    }
}

void Presenter::setup_test_slideshow() {
    slideshow->add(Slide::simple_centered_text_slide("Hello SFML", "droid", WHITE, GREEN));
    slideshow->add(Slide::simple_image_slide("cat", RED));
    slideshow->add(Slide::simple_centered_text_slide("Hello World!", "droid", GREEN, WHITE));
    slideshow->add(Slide::simple_centered_text_slide("Multi\nline\ntext", "droid"));
}

int Presenter::run() {
    if (slideshow->is_empty()) {
        cerr << "Slideshow has no slides. Exiting." << endl;
        return 1;
    }

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
                        slideshow->next_slide();
                        break;
                    case sf::Keyboard::P:
                    case sf::Keyboard::BackSpace:
                        slideshow->previous_slide();
                        break;
                    case sf::Keyboard::F:
                        window.toggle_fullscreen();
                        slideshow->recenter_content();
                        break;
                    default:
                        break;
                }
            }
        }

        slideshow->render_current_slide(window.window);
        window.window->display();
    }

    return 0;
}
