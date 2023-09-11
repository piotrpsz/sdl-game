//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#include "shared.h"
#include <random>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;


namespace shared {
    int scores{};
    bool is_running{true};

    f32 random_speed(f32 const start, f32 const end) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> distr(start, end);
        return static_cast<f32>(distr(gen));
    }

    SDL_Texture* texture_from_file(SDL_Renderer* const renderer, string const& path) noexcept {
        auto surface = IMG_Load(path.c_str());
        if (surface == nullptr) {
            SDL_Log("Failed to load texture file: %s", SDL_GetError());
            return nullptr;
        }
        auto texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            SDL_Log("Failed to convert surface to texture: %s", SDL_GetError());
            return nullptr;
        }
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_BEST);
        SDL_DestroySurface(surface);
        return texture;
    }

} // end of namespace
