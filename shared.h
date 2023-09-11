//
// Created by Piotr Pszczółkowski on 11/09/2023.
//

#ifndef SDL_GAME_SHARED_H
#define SDL_GAME_SHARED_H
#include "types.h"
#include <string>

namespace shared {
    f32 random_speed(f32 start, f32 end);
    SDL_Texture* texture_from_file(SDL_Renderer* renderer, std::string const& path) noexcept;
}




#endif //SDL_GAME_SHARED_H
