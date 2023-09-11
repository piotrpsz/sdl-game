//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#ifndef SDL_TEST_TYPES_H
#define SDL_TEST_TYPES_H
#include <cstdint>
#include <SDL3/SDL.h>

using u8 = uint8_t;
using u32 = uint32_t;
using f32 = float;

struct vec2_t { f32 x, y; };
using color_t = SDL_Color;
using rect_t = SDL_FRect;
using point_t = SDL_FPoint;

enum class ActorType {
    GENERAL,
    BALL,
    PADDLE_LEFT, PADDLE_RIGHT,
    WALL_TOP, WALL_BOTTOM, WALL_RIGHT
};

#endif //SDL_TEST_TYPES_H
