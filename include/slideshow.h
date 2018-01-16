#ifndef SLIDESHOW_H_
#define SLIDESHOW_H_

#include <vector>
#include <algorithm>
#include "font_manager.h"
#include "image_manager.h"
#include "slide.h"

struct Slideshow {
    std::vector<Slide> slides;
    uint32_t current_slide = 0;
    FontManager *font_manager;
    ImageManager *image_manager;

    Slideshow(FontManager &font_manager, ImageManager &image_manager);
    void add(const Slide &slide);
    void render_current_slide(sf::RenderWindow *window);
    void recenter_content();

    inline void next_slide() { current_slide = std::min(current_slide + 1, uint32_t(slides.size() - 1)); }
    inline void previous_slide() {
        if (current_slide > 0) {
            current_slide--;
        }
    }
};

#endif // SLIDESHOW_H_
