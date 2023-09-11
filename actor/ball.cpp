//
// Created by Piotr Pszczółkowski on 11/09/2023.
//

#include "ball.h"

void ball_t::update(f32 delta_time) noexcept {
    position_.x += velocity_.x * delta_time;
    position_.y += velocity_.y * delta_time;
}

void ball_t::output(SDL_Renderer* renderer) noexcept {
    rect_t const rect{position_.x - BALL_RADIUS, position_.y-BALL_RADIUS, BALL_DIAMETER, BALL_DIAMETER};
    if (SDL_RenderTexture(renderer, texture_, nullptr, &rect) != 0)
        SDL_Log("Failed to render texture: %s", SDL_GetError());
}
