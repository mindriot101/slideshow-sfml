#ifndef PRESENTER_H_
#define PRESENTER_H_

#include <memory>
#include "font_manager.h"
#include "image_manager.h"
#include "main_window.h"
#include "shader_manager.h"

struct Slideshow;

struct Presenter {
    FontManager font_manager;
    ImageManager image_manager;
    ShaderManager shader_manager;

    MainWindow window;
    std::unique_ptr<Slideshow> slideshow;

    Presenter(const std::string &root_dir);

    void setup_test_slideshow();

    int run();
};

#endif  // PRESENTER_H_
