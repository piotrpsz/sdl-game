#include "matrix3.h"

static f32 ident[3][3] = {
        { 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f },
        { 0.f, 0.f, 1.f }
};
const matrix3_t matrix3_t::identity(ident);
