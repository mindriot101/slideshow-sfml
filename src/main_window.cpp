#include "main_window.h"
#include "globals.h"

using namespace std;

MainWindow::MainWindow() {
    window = make_unique<sf::RenderWindow>(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Presentation",
        sf::Style::Default);
    window_width = WINDOW_WIDTH;
    window_height = WINDOW_HEIGHT;
}

void MainWindow::toggle_fullscreen() {
    fullscreen = !fullscreen;
    auto style = fullscreen ? sf::Style::Default | sf::Style::Fullscreen
                            : sf::Style::Default;
    window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Presentation",
                   style);
    auto res = window->getSize();
    scaling_factor = res.x / float(window_width);
}
