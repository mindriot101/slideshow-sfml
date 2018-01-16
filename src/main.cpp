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
#include "presenter.h"

using namespace std;

/* Have to hold the textures at constant points in memory
 * or else we lose the texture content when making sprites */
std::map<std::string, sf::Texture> TEXTURES;

int main() {
    Presenter presenter;
    return presenter.run();
}
