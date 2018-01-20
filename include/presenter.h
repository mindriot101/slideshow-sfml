#ifndef PRESENTER_H_
#define PRESENTER_H_

#include <memory>
#include "font_manager.h"
#include "image_manager.h"
#include "main_window.h"
#include "shader_manager.h"
#include "slide.h"
#include "config.h"

struct Slideshow;

template <typename T>
struct Option {
    T value;
    bool has_value;

    static Option<T> None() {
        Option option;
        option.has_value = false;
        return option;
    }

    static Option<T> Some(T value) {
        Option option;
        option.value = value;
        option.has_value = true;
        return option;
    }

    bool is_some() const {
        return has_value;
    }

    bool is_none() const {
        return !is_some();
    }

    operator bool() const {
        return is_some();
    }
};

struct Presenter {
    FontManager font_manager;
    ImageManager image_manager;
    ShaderManager shader_manager;

    std::unique_ptr<MainWindow> window;
    std::unique_ptr<Slideshow> slideshow;

    Presenter();

    void handle_line(const std::string &line, ConfigSection &section, Slide &current, Option<std::string> &current_shader);
    void parse_config(const std::string &filename);

    int run();
};

#endif  // PRESENTER_H_
