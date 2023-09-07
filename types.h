#ifndef SDL_TEST_TYPES_H
#define SDL_TEST_TYPES_H
#include <cstdint>

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;

struct color_t { u8 r, g, b, a; };
struct rect_t { f32 x, y, w, h; };
struct vec2_t { f32 x, y; };

#endif //SDL_TEST_TYPES_H
