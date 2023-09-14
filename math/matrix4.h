#ifndef SDL_GAME_MATRIX4_H
#define SDL_GAME_MATRIX4_H

#include "../types.h"
#include "vec3.h"
#include <cstdio>
#include <string>

class matrix4_t {
public:
    f32 m[4][4]{};

    explicit matrix4_t(f32 m[4][4]) {
        std::memcpy(m, m, 16 *sizeof(f32));
    }
    matrix4_t() { *this = matrix4_t{matrix4_t::identity}; }
    f32 const* operator()() { return &m[0][0]; }

    friend matrix4_t operator*(matrix4_t const& a, matrix4_t const& b) noexcept {
        matrix4_t r;

        r.m[0][0] =
                a.m[0][0] * b.m[0][0] +
                a.m[0][1] * b.m[1][0] +
                a.m[0][2] * b.m[2][0] +
                a.m[0][3] * b.m[3][0];
        r.m[0][1] =
                a.m[0][0] * b.m[0][1] +
                a.m[0][1] * b.m[1][1] +
                a.m[0][2] * b.m[2][1] +
                a.m[0][3] * b.m[3][1];
        r.m[0][2] =
                a.m[0][0] * b.m[0][2] +
                a.m[0][1] * b.m[1][2] +
                a.m[0][2] * b.m[2][2] +
                a.m[0][3] * b.m[3][2];
        r.m[0][3] =
                a.m[0][0] * b.m[0][3] +
                a.m[0][1] * b.m[1][3] +
                a.m[0][2] * b.m[2][3] +
                a.m[0][3] * b.m[3][3];

        r.m[1][0] =
                a.m[1][0] * b.m[0][0] +
                a.m[1][1] * b.m[1][0] +
                a.m[1][2] * b.m[2][0] +
                a.m[1][3] * b.m[3][0];
        r.m[1][1] =
                a.m[1][0] * b.m[0][1] +
                a.m[1][1] * b.m[1][1] +
                a.m[1][2] * b.m[2][1] +
                a.m[1][3] * b.m[3][1];
        r.m[1][2] =
                a.m[1][0] * b.m[0][2] +
                a.m[1][1] * b.m[1][2] +
                a.m[1][2] * b.m[2][2] +
                a.m[1][3] * b.m[3][2];
        r.m[1][3] =
                a.m[1][0] * b.m[0][3] +
                a.m[1][1] * b.m[1][3] +
                a.m[1][2] * b.m[2][3] +
                a.m[1][3] * b.m[3][3];

        r.m[2][0] =
                a.m[2][0] * b.m[0][0] +
                a.m[2][1] * b.m[1][0] +
                a.m[2][2] * b.m[2][0] +
                a.m[2][3] * b.m[3][0];
        r.m[2][1] =
                a.m[2][0] * b.m[0][1] +
                a.m[2][1] * b.m[1][1] +
                a.m[2][2] * b.m[2][1] +
                a.m[2][3] * b.m[3][1];
        r.m[2][2] =
                a.m[2][0] * b.m[0][2] +
                a.m[2][1] * b.m[1][2] +
                a.m[2][2] * b.m[2][2] +
                a.m[2][3] * b.m[3][2];
        r.m[2][3] =
                a.m[2][0] * b.m[0][3] +
                a.m[2][1] * b.m[1][3] +
                a.m[2][2] * b.m[2][3] +
                a.m[2][3] * b.m[3][3];

        r.m[3][0] =
                a.m[3][0] * b.m[0][0] +
                a.m[3][1] * b.m[1][0] +
                a.m[3][2] * b.m[2][0] +
                a.m[3][3] * b.m[3][0];
        r.m[3][1] =
                a.m[3][0] * b.m[0][1] +
                a.m[3][1] * b.m[1][1] +
                a.m[3][2] * b.m[2][1] +
                a.m[3][3] * b.m[3][1];
        r.m[3][2] =
                a.m[3][0] * b.m[0][2] +
                a.m[3][1] * b.m[1][2] +
                a.m[3][2] * b.m[2][2] +
                a.m[3][3] * b.m[3][2];
        r.m[3][3] =
                a.m[3][0] * b.m[0][3] +
                a.m[3][1] * b.m[1][3] +
                a.m[3][2] * b.m[2][3] +
                a.m[3][3] * b.m[3][3];

        return r;
    }

    matrix4_t& operator*=(matrix4_t const& rhs) noexcept {
        *this = *this * rhs;
        return *this;
    }
    [[nodiscard]] vec3_t translation() const noexcept {
        return vec3_t{m[3][0], m[3][1], m[3][2]};
    }
    [[nodiscard]] vec3_t x_axis() const noexcept {
        return vec3_t::normalize(vec3_t{m[0][0], m[0][1], m[0][2]});
    }
    [[nodiscard]] vec3_t y_axis() const noexcept {
        return vec3_t::normalize(vec3_t{m[1][0], m[1][1], m[1][2]});
    }
    [[nodiscard]] vec3_t z_axis() const noexcept {
        return vec3_t::normalize(vec3_t{m[2][0], m[2][1], m[2][2]});
    }
    vec3_t scale() const noexcept {
        return vec3_t{
                vec3_t{m[0][0], m[0][1], m[0][2]}.length(),
                vec3_t{m[1][0], m[1][1], m[1][2]}.length(),
                vec3_t{m[2][0], m[2][1], m[2][2]}.length()
        };
    }
    static matrix4_t scale(f32 const  xs, f32 const ys, f32 zs) noexcept {
        f32 tmp[4][4] = {
            { xs, 0.f, 0.f, 0.f },
            { 0.f, ys, 0.f, 0.f },
            { 0.f, 0.f, zs, 0.f },
            { 0.f, 0.f, 0.f, 1.f }
        };
        return matrix4_t{tmp};
    }
    static matrix4_t scale(vec3_t const& sv) noexcept {
        return scale(sv.x, sv.y, sv.z);
    }
    static matrix4_t scale(f32 const scalar) noexcept {
        return scale(scalar, scalar, scalar);
    }
    static matrix4_t rotation_x(f32 const theta) noexcept {
        f32 tmp[4][4] = {
                { 1.f, 0.f, 0.f , 0.f },
                { 0.f, std::cos(theta), std::sin(theta), 0.0f },
                { 0.f, -std::sin(theta), std::cos(theta), 0.0f },
                { 0.f, 0.f, 0.f, 1.f }
        };
        return matrix4_t{tmp};
    }
    static matrix4_t rotation_y(f32 const theta) noexcept {
        float tmp[4][4] = {
                { std::cos(theta), 0.f, -std::sin(theta), 0.f },
                { 0.f, 1.f, 0.f, 0.f },
                { std::sin(theta), 0.f, std::cos(theta), 0.f },
                { 0.f, 0.f, 0.f, 1.f }
        };
        return matrix4_t{tmp};
    }
    static matrix4_t rotation_z(f32 const theta) noexcept {
        f32 tmp[4][4] = {
                { std::cos(theta), std::sin(theta), 0.f, 0.f },
                { -std::sin(theta), std::cos(theta), 0.f, 0.f },
                { 0.f, 0.f, 1.f, 0.f },
                { 0.f, 0.f, 0.f, 1.f }
        };
        return matrix4_t{tmp};
    }



    static const matrix4_t identity;
};

#endif //SDL_GAME_MATRIX4_H
