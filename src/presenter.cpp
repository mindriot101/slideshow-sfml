#include "presenter.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include "slideshow.h"
#include "presenter_time.h"

using namespace std;

namespace {
    string join_prefix(const string &prefix, const string &path) {
        stringstream ss;
        ss << prefix << "/" << path;
        return ss.str();
    }

    template <typename T, typename Lambda>
        vector<T> take_while(const vector<T> inp, Lambda F) {
            vector<T> out;
            for (auto value : inp) {
                if (!F(value)) {
                    break;
                }

                out.push_back(value);
            }
            return out;
        }

    string parse_slide_text(const string &line, int *next_pos) {
        stringstream ss;
        bool collecting = false;
        for (auto c: line) {
            if (!collecting && (c == '"')) {
                collecting = true;
                continue;
            }

            if (collecting && (c == ' ')) {
                (*next_pos)++;
            }

            if (collecting && (c != '"')) {
                ss << c;
            }

            if (collecting && (c == '"')) {
                (*next_pos)++;
                break;
            }
        }

        return ss.str();
    }

}  // namespace

Presenter::Presenter() {
    if (!sf::Shader::isAvailable()) {
        cerr << "Shaders not available on this platform. Cannot continue."
            << endl;
        exit(EXIT_FAILURE);
    }

    slideshow = make_unique<Slideshow>(font_manager, image_manager, shader_manager);

    auto config_filename = "../config.txt";
    parse_config(config_filename);
}


void Presenter::parse_config(const string &filename) {
    ifstream ifs(filename);
    string line;

    ConfigSection section = ConfigSection::Defaults;
    Slide current;
    Option<string> current_shader = Option<string>::None();;

    while (getline(ifs, line)) {
        if (line.empty() || line == "\n") {
            continue;
        }
        handle_line(line, section, current, current_shader);
    }
}

void Presenter::handle_line(const string &line, ConfigSection &section, Slide &current, Option<string> &current_shader) {
    istringstream iss(line);
    vector<string> tokens{istream_iterator<string>(iss),
        istream_iterator<string>()};

    /* Remove anything after comments */
    vector<string> valid_tokens = take_while(tokens, [](string token) { return token != "#"; });
    if (valid_tokens.empty()) {
        return;
    }

    for (auto key: valid_tokens) {
        cout << key << " ";
    }
    cout << endl;

    auto tag = valid_tokens[0];
    if (tag == "resolution") {
        if (section != ConfigSection::Defaults) {
            cerr << "Resolution key belongs in the defaults section of the config file" << endl;
            exit(EXIT_FAILURE);
        }

        auto width_str = valid_tokens.at(1);
        auto height_str = valid_tokens.at(2);

        auto width = atoi(width_str.c_str());
        auto height = atoi(width_str.c_str());
        window = make_unique<MainWindow>(width, height);

    } else if (tag == "background_colour") {
        auto r = atoi(valid_tokens.at(1).c_str());
        auto g = atoi(valid_tokens.at(2).c_str());
        auto b = atoi(valid_tokens.at(3).c_str());
        auto colour = sf::Color(r, g, b);

        if (section == ConfigSection::Defaults) {
            slideshow->default_background_colour = colour;
        } else {
            current.background_colour = colour;
        }

    } else if (tag == "font") {
        if (section != ConfigSection::Defaults) {
            cerr << "Font definition belongs in the defaults section of the config file" << endl;
            exit(EXIT_FAILURE);
        }

        auto tag = valid_tokens.at(1);
        auto path = valid_tokens.at(2);
        font_manager.add(tag, path);

    } else if (tag == "image") {
        if (section != ConfigSection::Defaults) {
            cerr << "Image definition belongs in the defaults section of the config file" << endl;
            exit(EXIT_FAILURE);
        }

        auto tag = valid_tokens.at(1);
        auto path = valid_tokens.at(2);
        image_manager.add(tag, path);

    } else if (tag == "shader") {
        if (section != ConfigSection::Defaults) {
            cerr << "Shader definition belongs in the defaults section of the config file" << endl;
            exit(EXIT_FAILURE);
        }

        auto tag = valid_tokens.at(1);
        auto vert_path = valid_tokens.at(2);
        auto frag_path = valid_tokens.at(3);

        shader_manager.add(tag, vert_path, frag_path);

    } else if (tag == "slides") {
        if (section != ConfigSection::Defaults) {
            cerr << "Cannot declare new slides within slides section. Use `new_slide` command." << endl;
            exit(EXIT_FAILURE);
        }

        section = ConfigSection::Slides;

    } else if (tag == "text") {
        if (section != ConfigSection::Slides) {
            cerr << "Text definition belongs in a slide definition" << endl;
            exit(EXIT_FAILURE);
        }

        /* Need to do something to handle the text */
        int next_pos = 1;
        cout << next_pos << endl;
        auto text = parse_slide_text(line, &next_pos);
        cout << next_pos << endl;

        auto font_name = valid_tokens.at(next_pos++);
        sf::Color font_colour;
        font_colour.r = atoi(valid_tokens.at(next_pos++).c_str());
        font_colour.g = atoi(valid_tokens.at(next_pos++).c_str());
        font_colour.b = atoi(valid_tokens.at(next_pos++).c_str());

        auto component = SlideComponent::centered_text(text, font_name, font_colour);
        component.x = atof(valid_tokens.at(next_pos++).c_str());
        component.y = atof(valid_tokens.at(next_pos++).c_str());

        current.components.push_back(component);

    } else if (tag == "with") {
        if (section != ConfigSection::Slides) {
            cerr << "Shader definition belongs in a slide definition" << endl;
            exit(EXIT_FAILURE);
        }

        if (valid_tokens.at(1) != "shader") {
            cerr << "`with` command should be followed by `shader`" << endl;
            exit(EXIT_FAILURE);
        }

        auto shader_name = valid_tokens.at(2);
        current_shader = Option<string>::Some(shader_name);

    } else if (tag == "endwith") {
        if (section != ConfigSection::Slides) {
            cerr << "`endwith` statement belongs in a slide definition" << endl;
            exit(EXIT_FAILURE);
        } 

        /* Attach the current shader to the previous component */
        if (!current_shader) {
            cerr << "No shader has been set. This should not happen" << endl;
            exit(EXIT_FAILURE);
        }

        auto comp = current.last_component();
        comp->shader_name = current_shader;
        current_shader = Option<string>::None();

    } else if (tag == "new_slide") {
        if (section != ConfigSection::Slides) {
            cerr << "New slide declaration belongs in a slide definition" << endl;
            exit(EXIT_FAILURE);
        } 
        slideshow->add(current);
        current = {};

    } else if (tag == "end_slideshow") {
        slideshow->add(current);
        current = {};
    } else {
        cerr << "Unhandled tag: " << tag << endl;
        exit(EXIT_FAILURE);
    }
}

int Presenter::run() {
    if (slideshow->is_empty()) {
        cerr << "Slideshow has no slides. Exiting." << endl;
        return 1;
    }

    slideshow->print_current(slideshow->current_slide);

    sf::Clock clock;
    float seconds = 0;
    while (window->window->isOpen()) {
        sf::Event event;
        while (window->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->window->close();
            } else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::Q:
                        window->window->close();
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
                        window->toggle_fullscreen();
                        slideshow->recenter_content();
                        break;
                    default:
                        break;
                }
            }
        }

        auto elapsed = clock.restart();
        seconds += elapsed.asSeconds();

        Time time{elapsed.asSeconds(), seconds};
        slideshow->render_current_slide(window, time);
        window->window->display();
    }

    return 0;
}
