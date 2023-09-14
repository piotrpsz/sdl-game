//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#include "drawer.h"

void drawer_t::draw_circle(point_t const center, int const radius) const noexcept {
    auto v = radius * 8 * 35 / 49;
    auto const n = (v + 7) & -8;
    SDL_FPoint points[n];

    auto const diameter = radius * 2;
    int x = radius - 1;
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = tx - diameter;
    int count = 0;

    for ( ; x >= y; count += 8) {
        // Each of the following renders an octant of the circle
        points[count+0] = { center.x + x, center.y - y };
        points[count+1] = { center.x + x, center.y + y };
        points[count+2] = { center.x - x, center.y - y };
        points[count+3] = { center.x - x, center.y + y };
        points[count+4] = { center.x + y, center.y - x };
        points[count+5] = { center.x + y, center.y + x };
        points[count+6] = { center.x - y, center.y - x };
        points[count+7] = { center.x - y, center.y + x };

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
    SDL_RenderPoints(renderer_, points, count);
}

void drawer_t::draw_filled_circle(f32 x, f32 y, f32 radius) const noexcept {
    f32 offsetx{};
    f32 offsety{radius};
    f32 d{radius - 1};
    int status{};

    while (offsety >= offsetx) {
        status += SDL_RenderLine(renderer_, x - offsety, y + offsetx, x + offsety, y + offsetx);
        status += SDL_RenderLine(renderer_, x - offsetx, y + offsety, x + offsetx, y + offsety);
        status += SDL_RenderLine(renderer_, x - offsetx, y - offsety, x + offsetx, y - offsety);
        status += SDL_RenderLine(renderer_, x - offsety, y - offsetx, x + offsety, y - offsetx);

        if (status) {
            return;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}
