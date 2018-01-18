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

    sf::VideoMode mode;
    if (fullscreen) {
        mode = sf::VideoMode::getDesktopMode();
    } else {
        mode = sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
    }

    window->create(mode, "Presentation", style);
    scaling_factor = mode.width / float(window_width);
}
