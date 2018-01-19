#ifndef PRESENTER_H_
#define PRESENTER_H_

#include <memory>
#include "font_manager.h"
#include "image_manager.h"
#include "main_window.h"
#include "shader_manager.h"
#include "config.h"

struct Slideshow;

struct Presenter {
    FontManager font_manager;
    ImageManager image_manager;
    ShaderManager shader_manager;

    std::unique_ptr<MainWindow> window;
    std::unique_ptr<Slideshow> slideshow;

    Presenter();

    void setup_test_slideshow();
    void handle_line(const std::string &line, ConfigSection &section, unsigned int &slide_counter);
    void parse_config(const std::string &filename);

    int run();
};

#endif  // PRESENTER_H_
