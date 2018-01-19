#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>

#include "font_manager.h"
#include "globals.h"
#include "image_manager.h"
#include "main_window.h"
#include "presenter.h"
#include "slide.h"
#include "slide_component.h"
#include "slideshow.h"
#include "config.h"

using namespace std;

/* Have to hold the textures at constant points in memory
 * or else we lose the texture content when making sprites */
std::map<std::string, sf::Texture> TEXTURES;

int main() {

    Presenter presenter;
    return presenter.run();
}
