#pragma once

#include <SDL3/SDL.h>
#include <SDL_image.h>
#include "drawer.h"
#include "font_t.h"
#include "types.h"

enum class Direction {
    Unknown = 0,
    Up = -1,
    Down = 1
};

class game_c final{
    constexpr static f32 THICKNESS = 15;
    constexpr static f32 PADDLE_HEIGHT = 100.;
    constexpr static f32 WINDOW_WIDTH = 1200;
    constexpr static f32 WINDOW_HEIGHT = 700;
    constexpr static f32 TOP_BORDER = THICKNESS;
    constexpr static f32 BOTTOM_BORDER = WINDOW_HEIGHT - THICKNESS;
    constexpr static f32 RIGHT_BORDER = WINDOW_WIDTH - THICKNESS;
    constexpr static f32 BALL_RADIUS = THICKNESS/2.f;

    SDL_Window* window_{};
    font_t font{};
    SDL_Texture* ball_{};
    drawer_c drawer_{};
    bool is_running{true};
    u32 ticks_count_{};

    Direction paddle_direction_{Direction::Unknown};
    vec2_t paddle_pos_{};
    vec2_t ball_pos_{};
    vec2_t ball_velocity_{};

public:
    ~game_c() { shutdown(); }
    bool initialize() noexcept;
    void run_loop() noexcept;
    void shutdown() noexcept;

    void process_input() noexcept;
    void update_game() noexcept;
    void generate_output() noexcept;
};



