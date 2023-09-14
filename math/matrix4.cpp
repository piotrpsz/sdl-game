//
// Created by Piotr Pszczółkowski on 13/09/2023.
//

#include "matrix4.h"
static f32 ident[4][4] = {
        { 1.f, 0.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f, 0.f },
        { 0.f, 0.f, 1.f, 0.f },
        { 0.f, 0.f, 0.f, 1.f }
};
const matrix4_t matrix4_t::identity{ident};
