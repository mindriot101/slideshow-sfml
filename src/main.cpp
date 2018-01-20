#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <streambuf>
#include <string>
#include <vector>

#include "config.h"
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
    Presenter presenter;
    return presenter.run();
}
