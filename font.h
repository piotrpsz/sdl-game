//
// Created by Piotr Pszczółkowski on 10/09/2023.
//

#ifndef SDL_GAME_FONT_H
#define SDL_GAME_FONT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <string>
#include <optional>
#include <utility>
#include "types.h"

class font_t final {
    std::unordered_map<int, TTF_Font*> data_;
public:
    bool load(std::string const& file_name) noexcept;
    std::optional<std::pair<f32, f32>> text_geometry(std::string const& text, int size) const noexcept;
    std::optional<SDL_Texture*> render_text(SDL_Renderer* renderer, std::string const& text, int size, SDL_Color color) const noexcept;
};


#endif //SDL_GAME_FONT_H
