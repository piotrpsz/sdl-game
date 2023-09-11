//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#ifndef SDL_GAME_LABEL_H
#define SDL_GAME_LABEL_H

#include <string>
#include <optional>
#include "../types.h"
#include "../font.h"

class drawer_t;

class label_t {
    static constexpr color_t COLOR{0, 0, 0, 255};

    std::string text_{};
    std::string str_{};
    font_t font_{};
    point_t position_{};
    size_t size_{};
    int* var_{};
public:
    label_t() = default;
    label_t(std::string text, point_t pos, size_t size, int* const var)
        : text_{std::move(text)}, position_{pos}, size_{size}, var_{var} {
        font_.load("/Users/piotr/Projects/cpp/sdl-game/assets/Carlito-Regular.ttf");
        // "/System/Library/Fonts/Helvetica.ttc"
    }

    void update() noexcept;
    void output(drawer_t const& drawer) const noexcept;
};


#endif //SDL_GAME_LABEL_H
