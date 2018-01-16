#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <iostream>
#include <SFML/Graphics.hpp>

struct MainWindow {
    sf::RenderWindow *window = nullptr;
    bool fullscreen = false;

    MainWindow();
    ~MainWindow();

    void toggle_fullscreen();

    private:

    static sf::RenderWindow *create_window(bool fullscreen);
};

#endif // MAIN_WINDOW_H_
