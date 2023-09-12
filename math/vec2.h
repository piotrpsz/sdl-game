#ifndef SDL_GAME_VEC2_H
#define SDL_GAME_VEC2_H

#include "../types.h"


class vec2_t final {
public:
    f32 x{}, y{};

    void set(f32 a, f32 b) noexcept {
        x = a;
        y = b;
    }

    vec2_t& operator*=(f32 scalar) noexcept {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    vec2_t& operator+=(vec2_t const& rhs) noexcept {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    vec2_t& operator-=(vec2_t const& rhs) noexcept {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    [[nodiscard]] f32 squared_length() const noexcept {
        return x*x + y*y;
    }

    [[nodiscard]] f32 length() const noexcept {
        return sqrtf(squared_length());
    }
};

#endif //SDL_GAME_VEC2_H
