#include "config.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

namespace {
    enum class ConfigSection {
        Defaults,
        Slides,
    };

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

    void handle_line(const string &line, Config &config, ConfigSection &section) {
        istringstream iss(line);
        vector<string> tokens{istream_iterator<string>(iss),
                              istream_iterator<string>()};

        /* Remove anything after comments */
        vector<string> valid_tokens = take_while(tokens, [](string token) { return token != "#"; });
        if (valid_tokens.empty()) {
            return;
        }

        cout << "--- ";
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
        } else if (tag == "background_colour") {
        } else if (tag == "font") {
            if (section != ConfigSection::Defaults) {
                cerr << "Font definition belongs in the defaults section of the config file" << endl;
                exit(EXIT_FAILURE);
            }
        } else if (tag == "image") {
            if (section != ConfigSection::Defaults) {
                cerr << "Image definition belongs in the defaults section of the config file" << endl;
                exit(EXIT_FAILURE);
            }
        } else if (tag == "shader") {
            if (section != ConfigSection::Defaults) {
                cerr << "Shader definition belongs in the defaults section of the config file" << endl;
                exit(EXIT_FAILURE);
            }
        } else if (tag == "slides") {
            assert(section == ConfigSection::Defaults);
            section = ConfigSection::Slides;
        } else if (tag == "text") {
            if (section != ConfigSection::Slides) {
                cerr << "Text definition belongs in a slide definition" << endl;
                exit(EXIT_FAILURE);
            }
        } else {
            cerr << "Unhandled tag: " << tag << endl;
            exit(EXIT_FAILURE);
        }
    }
}

Config Config::parse(const string &filename) {
    Config config;

    ifstream ifs(filename);
    string line;

    ConfigSection section = ConfigSection::Defaults;

    while (getline(ifs, line)) {
        if (line.empty() || line == "\n") {
            continue;
        }
        handle_line(line, config, section);
    }

    exit(0);

    return config;
}
