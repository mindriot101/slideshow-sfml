#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

struct MainWindow {
    std::unique_ptr<sf::RenderWindow> window;
    bool fullscreen = false;
    unsigned int window_width = 0;
    unsigned int window_height = 0;

    MainWindow();

    void toggle_fullscreen();
};

#endif  // MAIN_WINDOW_H_
