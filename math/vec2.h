#ifndef SDL_GAME_VEC2_H
#define SDL_GAME_VEC2_H

#include "../types.h"
#include <cmath>

class vec2_t final {
public:
    static const vec2_t Zero;
    static const vec2_t UnitX;
    static const vec2_t UnitY;
    static const vec2_t NegUnitX;
    static const vec2_t NegUnitY;

    f32 x{}, y{};


    void set(f32 a, f32 b) noexcept {
        x = a;
        y = b;
    }
    friend vec2_t operator+(vec2_t const a, vec2_t const b) noexcept {
        return vec2_t{a.x + b.x, a.y + b.y};
    }
    friend vec2_t operator-(vec2_t const a, vec2_t const b) noexcept {
        return vec2_t{a.x - b.x, a.y - b.y};
    }
    friend vec2_t operator*(vec2_t const a, vec2_t const b) noexcept {
        return vec2_t{a.x * b.x, a.y * b.y};
    }
    friend vec2_t operator*(vec2_t const a, f32 const scalar) noexcept {
        return vec2_t{a.x * scalar, a.y * scalar};
    }
    friend vec2_t operator*(f32 const scalar, vec2_t const a) noexcept {
        return vec2_t{a.x * scalar, a.y * scalar};
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
        return std::sqrtf(squared_length());
    }
    void normalize() noexcept {
        f32 const n{length()};
        x /= n;
        y /= n;
    }
    static vec2_t normalize(vec2_t const vec) noexcept{
        auto tmp{vec};
        tmp.normalize();
        return tmp;
    }
    static f32 dot(vec2_t a, vec2_t b) noexcept {
        return a.x*b.x + a.y*b.y;
    }
    static vec2_t lerp(vec2_t const a, vec2_t const b, f32 const f) noexcept {
        return a + f*(b - a);
    }
    static vec2_t reflect(vec2_t const v, vec2_t n) noexcept {
        return v - 2.f * vec2_t::dot(v, n) * n;
    }


};

inline static vec2_t Zero{0.0f, 0.0f};

#endif //SDL_GAME_VEC2_H
