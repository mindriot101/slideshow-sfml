#include "main_window.h"
#include "globals.h"

MainWindow::MainWindow() {
    window = MainWindow::create_window(false);
}

void MainWindow::toggle_fullscreen() {
    window->close();
    delete window;

    fullscreen = !fullscreen;
    window = MainWindow::create_window(fullscreen);
}

MainWindow::~MainWindow() {
    if (window != nullptr) {
        delete window;
    }
}

sf::RenderWindow *MainWindow::create_window(bool fullscreen) {
    auto style = fullscreen ? sf::Style::Default | sf::Style::Fullscreen : sf::Style::Default;
    auto *window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Presentation", style);
    if (window == nullptr) {
        std::cerr << "Error creating render window" << std::endl;
        exit(EXIT_FAILURE);
    }
    window->setVerticalSyncEnabled(true);
    return window;
}
