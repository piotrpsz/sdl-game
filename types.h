#ifndef SDL_TEST_TYPES_H
#define SDL_TEST_TYPES_H
#include <cstdint>
#include <SDL3/SDL.h>

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;

struct color_t { u8 r, g, b, a; };
struct vec2_t { f32 x, y; };
using rect_t = SDL_FRect;
using point_t = SDL_FPoint;

#endif //SDL_TEST_TYPES_H
