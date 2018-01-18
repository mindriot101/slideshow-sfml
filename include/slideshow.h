#ifndef SLIDESHOW_H_
#define SLIDESHOW_H_

#include <algorithm>
#include <memory>
#include <vector>
#include "font_manager.h"
#include "shader_manager.h"
#include "main_window.h"
#include "image_manager.h"
#include "slide.h"

struct Slideshow {
    std::vector<Slide> slides;
    uint32_t current_slide = 0;
    FontManager *font_manager;
    ImageManager *image_manager;
    ShaderManager *shader_manager;
    float scaling_factor = 1.0f;

    Slideshow(FontManager &font_manager, ImageManager &image_manager, ShaderManager &shader_manager);
    void add(const Slide &slide);
    void render_current_slide(const MainWindow &main_window);
    Slide *last();
    void recenter_content();
    bool is_empty() const;

    void next_slide();
    void previous_slide();

    void print_current(int current_slide);
};

#endif  // SLIDESHOW_H_
