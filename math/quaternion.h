#ifndef SDL_GAME_QUATERNION_H
#define SDL_GAME_QUATERNION_H

#include "../types.h"
#include "vec3.h"
#include <cmath>

class quaternion_t {
public:
    f32 x{}, y{}, z{}, w{};

    quaternion_t() { *this = quaternion_t::identity; }
    explicit quaternion_t(f32 a, f32 b, f32 c, f32 d)
            : x{a}, y{b}, z{c}, w{d} {
    }
    explicit quaternion_t(vec3_t const& axis, f32 const angle) {
        f32 const scalar = std::sin(angle / 2.f);
        x = axis.x * scalar;
        y = axis.y * scalar;
        z = axis.z * scalar;
        w = std::cos(angle / 2.0);
    }

    void set(f32 const a, f32 const b, f32 const c, f32 const d) noexcept {
        x = a;
        y = b;
        z = c;
        w = d;
    }
    void conjugate() noexcept {
        x *= -1.0f;
        y *= -1.0f;
        z *= -1.0f;
    }
    [[nodiscard]] f32 length_squared() const noexcept {
        return x*x + y*y + z*z + w*w;
    }
    [[nodiscard]] f32 length() const noexcept {
        return std::sqrt(length_squared());
    }
    void normalize() noexcept {
        f32 const n = length();
        x /= n;
        y /= n;
        z /= n;
        w /= n;
    }
    static quaternion_t normalize(quaternion_t const& q) noexcept {
        quaternion_t tmp{q};
        tmp.normalize();
        return tmp;
    }
//    static quaternion_t lerp(quaternion_t const& a, quaternion_t const& b, f32 const f) {
//        Quaternion retVal;
//        retVal.x = Math::Lerp(a.x, b.x, f);
//        retVal.y = Math::Lerp(a.y, b.y, f);
//        retVal.z = Math::Lerp(a.z, b.z, f);
//        retVal.w = Math::Lerp(a.w, b.w, f);
//        retVal.Normalize();
//        return retVal;
//    }

    static const quaternion_t identity;
};


#endif //SDL_GAME_QUATERNION_H
