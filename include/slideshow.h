#ifndef SLIDESHOW_H_
#define SLIDESHOW_H_

#include <algorithm>
#include <memory>
#include <vector>
#include "font_manager.h"
#include "image_manager.h"
#include "main_window.h"
#include "presenter_time.h"
#include "shader_manager.h"
#include "slide.h"

struct Slideshow {
    std::vector<Slide> slides;
    uint32_t current_slide = 0;
    FontManager *font_manager;
    ImageManager *image_manager;
    ShaderManager *shader_manager;
    float scaling_factor = 1.0f;
    sf::Color default_background_colour;

    Slideshow(FontManager &font_manager, ImageManager &image_manager,
              ShaderManager &shader_manager);
    void add(const Slide &slide);
    void render_current_slide(const std::unique_ptr<MainWindow> &main_window,
                              const Time &time);
    Slide *last();
    void recenter_content();
    bool is_empty() const;

    void next_slide();
    void previous_slide();

    void print_current(int current_slide);
};

#endif  // SLIDESHOW_H_
