//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#include "wall.h"
#include "../drawer.h"

void wall_t::output(drawer_t const& drawer) const noexcept {
    drawer.draw_color(COLOR);
    drawer.fill_rect(rect_);
}
