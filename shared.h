//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#ifndef SDL_GAME_SHARED_H
#define SDL_GAME_SHARED_H
#include "types.h"
#include <string>

namespace shared {
    inline static f32 const THICKNESS = 15.f;
    inline static f32 const WINDOW_WIDTH = 1200;
    inline static f32 const WINDOW_HEIGHT = 700;
    inline static f32 TOP_BORDER = THICKNESS;
    inline static f32 BOTTOM_BORDER = WINDOW_HEIGHT - THICKNESS;
    inline static f32 RIGHT_BORDER = WINDOW_WIDTH - THICKNESS;

    extern  int scores;
    extern bool is_running;

    f32 random_speed(f32 start, f32 end);
    SDL_Texture* texture_from_file(SDL_Renderer* renderer, std::string const& path) noexcept;
}




#endif //SDL_GAME_SHARED_H
