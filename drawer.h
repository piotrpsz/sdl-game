#ifndef SDL_TEST_DRAWER_H
#define SDL_TEST_DRAWER_H

#include <SDL3/SDL.h>
#include <iostream>
#include "types.h"

class drawer_c final {
    SDL_Renderer *renderer_;
public:
    drawer_c() = default;

    ~drawer_c() = default;

    explicit drawer_c(SDL_Window *const w) {
        auto const flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        if (auto r = SDL_CreateRenderer(w, nullptr, flags); r) {
            renderer_ = r;
            return;
        }
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
    }

    void destroy() {
        if (renderer_) {
            SDL_DestroyRenderer(renderer_);
            renderer_ = nullptr;
        }
    }

    SDL_Renderer* operator()() {
        return renderer_;
    }

    [[nodiscard]] bool ok() const noexcept {
        return renderer_ != nullptr;
    }

    void draw_color(u8 const r, u8 const g, u8 const b, u8 const a) {
        if (SDL_SetRenderDrawColor(renderer_, r, g, b, a) != 0)
            SDL_Log("Failed to set color(1)");
    }

    void draw_color(color_t c) {
        if (SDL_SetRenderDrawColor(renderer_, c.r, c.g, c.b, c.a) != 0)
            SDL_Log("Failed to set color(2): %s", SDL_GetError());
    }

    void fill_rect(rect_t const r) const noexcept {
        if (SDL_RenderFillRect(renderer_, &r) != 0)
            SDL_Log("Failed to draw filled rect: %s", SDL_GetError());
    }

    void clear() const noexcept {
        if (SDL_RenderClear(renderer_) != 0)
            SDL_Log("Failed to clear: %s", SDL_GetError());
    }

    void present() const noexcept {
        if (SDL_RenderPresent(renderer_) != 0)
            SDL_Log("Failed to present: %s", SDL_GetError());
    }

    void draw_circle(point_t center, int radius) const noexcept;
};


#endif //SDL_TEST_DRAWER_H
