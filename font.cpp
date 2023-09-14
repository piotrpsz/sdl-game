//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#include "font.h"
#include <vector>
#include <iostream>
using namespace std;

bool font_t::load(std::string const& file_name) noexcept {
    vector<int> const font_sizes {
        8, 9, 10, 11, 12, 14, 16, 20, 22, 24, 26, 28,
        30, 32, 34, 36, 38, 42, 44, 46, 48, 52, 56,
        60, 64, 68, 71
    };
    for (auto size: font_sizes) {
        auto font = TTF_OpenFont(file_name.c_str(), size);
        if (!font) {
            SDL_Log("Failed to load font %s in size %d ", file_name.c_str(), size);
            return false;
        }
        data_.emplace(size, font);
    }
    return true;
}

optional<pair<f32, f32>> font_t::text_geometry(const std::string& text, int size) const noexcept {
    int width{}, height{};

    if (auto it = data_.find(size); it != data_.end()) {
        TTF_SetFontStyle(it->second, TTF_STYLE_BOLD);
        if (TTF_SizeText(it->second, text.c_str(), &width, &height) == 0)
            return make_pair(static_cast<f32>(width), static_cast<f32>(height));
    }

    return nullopt;
}

optional<SDL_Texture*> font_t::render_text(SDL_Renderer* const renderer, std::string const& text, int size, color_t color) const noexcept {
    if (auto it = data_.find(size); it != data_.end()) {
//        if (auto surface = TTF_RenderUTF8_Blended(it->second, text.c_str(), color); surface) {
        if (auto surface = TTF_RenderText_Blended(it->second, text.c_str(), color); surface) {
            auto texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == nullptr) {
                SDL_Log("Failed to create text textutr from surface");
                return nullopt;
            }
            SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_BEST);
            return texture;
        }
    }
    return nullopt;
}
