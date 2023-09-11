//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#ifndef SDL_GAME_WALL_H
#define SDL_GAME_WALL_H

#include "../types.h"

// forward declarations
class drawer_t;

class wall_t {
    static constexpr color_t COLOR{255, 255, 255, 255};
    rect_t rect_;
    ActorType type_;
public:
    wall_t() = default;
    wall_t(rect_t rect, ActorType type) : rect_{rect}, type_{type} {}

    [[nodiscard]] ActorType type() const noexcept { return type_; }

    void output(drawer_t const& drawer) const noexcept;
};

#endif //SDL_GAME_WALL_H
