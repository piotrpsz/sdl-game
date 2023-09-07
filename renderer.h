#ifndef SDL_TEST_RENDERER_H
#define SDL_TEST_RENDERER_H

#include <SDL3/SDL.h>
#include "types.h"

class renderer_c final {
    SDL_Renderer *renderer_{nullptr};
public:
    renderer_c() = default;
    explicit renderer_c(SDL_Window *const window) {
        auto const flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
        auto const renderer =  SDL_CreateRenderer(window, nullptr, flags);
        if (renderer) {
            renderer_ = renderer;
            return;
        }
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
    }

};


#endif //SDL_TEST_RENDERER_H
