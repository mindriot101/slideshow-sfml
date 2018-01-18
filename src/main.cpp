#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

#include "picojson.h"

#include "font_manager.h"
#include "globals.h"
#include "image_manager.h"
#include "main_window.h"
#include "presenter.h"
#include "slide.h"
#include "slide_component.h"
#include "slideshow.h"

using namespace std;

/* Have to hold the textures at constant points in memory
 * or else we lose the texture content when making sprites */
std::map<std::string, sf::Texture> TEXTURES;


int main() {

    /* Parse the toml code */
    auto filename = "../config.json";
    ifstream ifs(filename);
    string text((istreambuf_iterator<char>(ifs)),
                 istreambuf_iterator<char>());

    picojson::value v;
    auto err = picojson::parse(v, text);
    if (!err.empty()) {
        cerr << err << endl;
        return EXIT_FAILURE;
    }


    return 0;

    Presenter presenter("..");
    return presenter.run();
}
