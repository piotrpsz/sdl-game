#ifndef SDL_GAME_MATRIX3_H
#define SDL_GAME_MATRIX3_H

#include "../types.h"
#include "vec2.h"
#include <string>
#include <cmath>

class matrix3_t {
public:
    f32 m[3][3]{};

    matrix3_t() { *this = matrix3_t::identity; }
    explicit matrix3_t(f32 matrix[3][3]) {
        std::memcpy(m, matrix, 9 * sizeof(float));
    }

    f32 const* operator()() const noexcept { return &m[0][0]; }

    friend matrix3_t operator*(matrix3_t const& a, matrix3_t const& b) noexcept {
        matrix3_t r;

        r.m[0][0] =
                a.m[0][0] * b.m[0][0] +
                a.m[0][1] * b.m[1][0] +
                a.m[0][2] * b.m[2][0];
        r.m[0][1] =
                a.m[0][0] * b.m[0][1] +
                a.m[0][1] * b.m[1][1] +
                a.m[0][2] * b.m[2][1];
        r.m[0][2] =
                a.m[0][0] * b.m[0][2] +
                a.m[0][1] * b.m[1][2] +
                a.m[0][2] * b.m[2][2];

        r.m[1][0] =
                a.m[1][0] * b.m[0][0] +
                a.m[1][1] * b.m[1][0] +
                a.m[1][2] * b.m[2][0];
        r.m[1][1] =
                a.m[1][0] * b.m[0][1] +
                a.m[1][1] * b.m[1][1] +
                a.m[1][2] * b.m[2][1];
        r.m[1][2] =
                a.m[1][0] * b.m[0][2] +
                a.m[1][1] * b.m[1][2] +
                a.m[1][2] * b.m[2][2];

        r.m[2][0] =
                a.m[2][0] * b.m[0][0] +
                a.m[2][1] * b.m[1][0] +
                a.m[2][2] * b.m[2][0];
        r.m[2][1] =
                a.m[2][0] * b.m[0][1] +
                a.m[2][1] * b.m[1][1] +
                a.m[2][2] * b.m[2][1];
        r.m[2][2] =
                a.m[2][0] * b.m[0][2] +
                a.m[2][1] * b.m[1][2] +
                a.m[2][2] * b.m[2][2];

        return r;
    }

    matrix3_t& operator*=(matrix3_t const rhs) noexcept {
        *this = *this * rhs;
        return *this;
    }
   static matrix3_t scale(f32 const xs, f32 const ys) noexcept {
        float tmp[3][3] = {
                { xs, 0.f, 0.f },
                { 0.f, ys, 0.f },
                { 0.f, 0.f, 1.f }
        };
        return matrix3_t{tmp};
    }
    static matrix3_t scale(vec2_t const& sv) noexcept {
        return scale(sv.x, sv.y);
    }
    static matrix3_t scale(f32 const v) noexcept {
        return scale(v, v);
    }
    // Create a rotation matrix about the Z axis
    // theta is in radians
    static matrix3_t rotation(f32 const theta) noexcept {
        f32 tmp[3][3] = {
                { std::cos(theta), std::sin(theta), 0.f },
                { -std::sin(theta), std::cos(theta), 0.f },
                { 0.f, 0.f, 1.f }
        };
        return matrix3_t(tmp);
    }
    // Create a translation matrix (on the xy-plane)
    static matrix3_t translation(vec2_t const& t) noexcept {
        f32 tmp[3][3] = {
                { 1.f, 0.f, 0.f },
                { 0.f, 1.f, 0.f },
                { t.x, t.y, 1.f }
        };
        return matrix3_t(tmp);
    }
    static const matrix3_t identity;
};


#endif //SDL_GAME_MATRIX3_H
