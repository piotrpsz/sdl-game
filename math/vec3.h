#ifndef SDL_GAME_VEC3_H
#define SDL_GAME_VEC3_H

#include "../types.h"
#include <cmath>

class vec3_t {
public:
    f32 x{}, y{}, z{};

    void set(f32 a, f32 b, f32 c) noexcept {
        x = a; y = b; z = c;
    }
    friend vec3_t operator+(vec3_t const& lhs, vec3_t const& rhs) noexcept {
        return vec3_t{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
    }
    friend vec3_t operator-(vec3_t const& lhs, vec3_t const& rhs) noexcept {
        return vec3_t{lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    }
    friend vec3_t operator*(vec3_t const& lhs, vec3_t const& rhs) noexcept {
        return vec3_t{lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
    }
    friend vec3_t operator*(vec3_t const&& v, f32 const scalar) noexcept {
        return vec3_t{v.x * scalar, v.y * scalar, v.z * scalar};
    }
    friend vec3_t operator*(f32 scalar, vec3_t const& v) noexcept {
        return vec3_t{v.x * scalar, v.y * scalar, v.z * scalar};
    }
    vec3_t& operator*=(f32 const scalar) noexcept {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    vec3_t& operator+=(vec3_t const& rhs) noexcept {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    vec3_t& operator-=(vec3_t const& rhs) noexcept {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }
    [[nodiscard]] f32 squared_length() const noexcept {
        return (x*x + y*y + z*z);
    }
    [[nodiscard]] f32 length() const noexcept {
        return (std::sqrtf(squared_length()));
    }
    void normalize() noexcept {
        f32 const n{length()};
        x /= n;
        y /= n;
        z /= n;
    }
    static vec3_t normalize(vec3_t const& v) noexcept {
        vec3_t tmp{v};
        tmp.normalize();
        return tmp;
    }
    static f32 dot(vec3_t const& lhs, vec3_t const& rhs) noexcept {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }
    static vec3_t cross(vec3_t const& lhs, vec3_t const& rhs) noexcept {
        return vec3_t{
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x,
        };
    }
    static vec3_t lerp(vec3_t const& lhs, vec3_t const& rhs, f32 const f) noexcept {
        return lhs + f * (rhs - lhs);
    }
    static vec3_t reflect(vec3_t const& v, vec3_t const& n) noexcept {
        return v - 2.f * vec3_t::dot(v, n) * n;
    }

};


#endif //SDL_GAME_VEC3_H
