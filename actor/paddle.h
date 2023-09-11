//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#ifndef SDL_GAME_PADDLE_H
#define SDL_GAME_PADDLE_H

#include "../types.h"
#include "../drawer.h"
#include <iostream>

// forward declaration
class actors_t;

class paddle_t final {
    constexpr static f32 GAP_FROM_BORDER = 1.f;
    constexpr static f32 SPEED = 200.f;

    enum class Direction {
        Unknown = 0,
        Up = -1,
        Down = 1
    };
    Direction direction_{Direction::Unknown};
    vec2_t position_{};
    ActorType type_{ActorType::PADDLE};
public:
    constexpr static f32 HEIGHT = 100.;
    constexpr static f32 WIDTH = 5.f;
public:
    paddle_t() = default;
    paddle_t(vec2_t const pos) : position_(pos) {}

    ActorType type() const noexcept { return type_; }
    vec2_t& pos() noexcept { return position_; }
    vec2_t const& pos() const noexcept { return position_; }
    void input(u8 const *state) noexcept;
    void update(f32 delta_time, actors_t const& actors) noexcept;
    void output(drawer_c const& drawer) const noexcept;

    friend std::ostream &operator<<(std::ostream &s, paddle_t const &f);
};


#endif //SDL_GAME_PADDLE_H
