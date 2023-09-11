//
// Created by Piotr Pszczółkowski on 11/09/2023.
//

#include "label.h"
#include <sstream>
#include "../shared.h"
#include "../font.h"
#include "../drawer.h"
using namespace std;

void label_t::update() noexcept {
    stringstream ss;
    ss << text_ << *var_;
    str_ = ss.str();
}

void label_t::output(drawer_t const& drawer) const noexcept {
//    auto const size = 14;
    if (auto const geometry = font_.text_geometry(text_, size_)) {
        auto const [w, h] = *geometry;
        rect_t const output_rect{position_.x, position_.y, w, h};
        if (auto const texture = font_.render_text(drawer(), str_, size_, COLOR))
            drawer.render_texture(*texture, output_rect);
    }
}
