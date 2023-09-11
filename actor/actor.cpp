//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#include "actor.h"
#include <iostream>
using namespace std;

void actors_t::input(u8 const *state) noexcept {
    for (auto& it : data_) {
        if (auto const paddle = std::get_if<paddle_t>(&it))
            paddle->input(state);
    }
}

void actors_t::update(f32 delta_time) noexcept {
    for (auto& it : data_) {
        if (auto ball = std::get_if<ball_t>(&it))
            ball->update(delta_time, *this);
        else if (auto paddle = std::get_if<paddle_t>(&it))
            paddle->update(delta_time, *this);
    }
}

void actors_t::output(drawer_c const& drawer) const noexcept {
    for (auto& it : data_) {
        if (auto const& ball = std::get_if<ball_t>(&it))
            ball->output(drawer);
        else if (auto const& paddle = std::get_if<paddle_t>(&it))
            paddle->output(drawer);
    }
}

