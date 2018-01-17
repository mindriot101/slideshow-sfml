#include "presenter.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "slideshow.h"

using namespace std;

namespace {
string join_prefix(const string &prefix, const string &path) {
    stringstream ss;
    ss << prefix << "/" << path;
    return ss.str();
}
}  // namespace

Presenter::Presenter(const string &root_dir) {
    if (!sf::Shader::isAvailable()) {
        cerr << "Shaders not available on this platform. Cannot continue."
             << endl;
        exit(EXIT_FAILURE);
    }

    font_manager.add("droid",
                     join_prefix(root_dir, "run_tree/fonts/DroidSansMono.ttf"));
    image_manager.add("cat", join_prefix(root_dir, "run_tree/images/cat.png"));
    shader_manager.add("green",
                       join_prefix(root_dir, "run_tree/shaders/green.glslv"),
                       join_prefix(root_dir, "run_tree/shaders/green.glslf"));

    slideshow = make_unique<Slideshow>(font_manager, image_manager, shader_manager);
    setup_test_slideshow();
}

void Presenter::setup_test_slideshow() {
    slideshow->add(
        Slide::simple_centered_text_slide("Hello SFML", "droid", WHITE, GREEN));
    slideshow->add(Slide::simple_image_slide("cat", RED));
    slideshow->add(Slide::simple_centered_text_slide("Hello World!", "droid",
                                                     WHITE, BLACK));
    slideshow->last()->last_component()->use_shader("green");
    slideshow->add(
        Slide::simple_centered_text_slide("Multi\nline\ntext", "droid"));
}

int Presenter::run() {
    if (slideshow->is_empty()) {
        cerr << "Slideshow has no slides. Exiting." << endl;
        return 1;
    }

    slideshow->print_current(slideshow->current_slide);

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
