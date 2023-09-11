//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#include "paddle.h"
#include "../shared.h"
using namespace std;

void paddle_t::input(u8 const *state) noexcept {
    direction_ = Direction::Unknown;
    if (state[SDL_SCANCODE_UP])
        direction_ = Direction::Up;
    else if (state[SDL_SCANCODE_DOWN])
        direction_ = Direction::Down;
}

void paddle_t::update(f32 delta_time, actors_t const& actors) noexcept {
    if (direction_ == Direction::Up) {
        position_.y += -SPEED * delta_time;
        if (position_.y < (HEIGHT / 2.f + shared::THICKNESS + GAP_FROM_BORDER))
            position_.y = HEIGHT / 2.f + shared::THICKNESS + GAP_FROM_BORDER;
    } else if (direction_ == Direction::Down) {
        position_.y += SPEED * delta_time;
        if (position_.y > (shared::WINDOW_HEIGHT - HEIGHT / 2.f - shared::THICKNESS - GAP_FROM_BORDER))
            position_.y = shared::WINDOW_HEIGHT - HEIGHT / 2.f - shared::THICKNESS - GAP_FROM_BORDER;
    }
}

void paddle_t::output(drawer_c const& drawer) const noexcept {
    drawer.draw_color({255, 0, 0, 255});
    drawer.fill_rect({position_.x - WIDTH/2.f, position_.y - HEIGHT/2.f, WIDTH, HEIGHT});
}

ostream& operator<<(ostream& s, paddle_t const& b) {
    s << "paddle(" << b.position_.x << "," << b.position_.y << ")";
    return s;
}
