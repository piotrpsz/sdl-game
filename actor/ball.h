//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#ifndef SDL_GAME_BALL_H
#define SDL_GAME_BALL_H

#include "../types.h"
#include "../shared.h"
#include "../drawer.h"
#include <iostream>
#include <string>
#include <SDL.h>

// forward declaration
class actors_t;

class ball_t final {
    static constexpr f32 BALL_RADIUS = 7.f;
    static constexpr f32 BALL_DIAMETER = 2.f * BALL_RADIUS;

    vec2_t center_{};
    vec2_t position_{};
    vec2_t velocity_{};
    ActorType type_{ActorType::BALL};
    SDL_Texture* texture_;
public:
    explicit ball_t(vec2_t const pos, SDL_Texture* const texture)
            : position_(pos)
            , velocity_({shared::random_speed(-100.0f, -70.f), shared::random_speed(70.f, 100.f)})
            , texture_{texture} {
    }
    ball_t() = default;
    ball_t(ball_t const&) = default;
    ball_t& operator=(ball_t const&) = default;
    ball_t(ball_t&&) = default;
    ball_t& operator=(ball_t&&) = default;


    ActorType type() const noexcept { return type_; }
    vec2_t& center() noexcept { return center_; }
    vec2_t const& center() const noexcept { return center_; }
    vec2_t& pos() noexcept { return position_; }
    vec2_t const& pos() const noexcept { return position_; }
    vec2_t& v() noexcept { return velocity_; }
    vec2_t const& v() const noexcept { return velocity_; }

    void update(f32 delta_time, actors_t& actors) noexcept;
    void output(drawer_t const& drawer) const noexcept;

    friend std::ostream &operator<<(std::ostream &s, ball_t const &f);
};


#endif //SDL_GAME_BALL_H
