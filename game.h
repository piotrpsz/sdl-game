//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#pragma once

#include <SDL3/SDL.h>
#include <SDL_image.h>
#include "drawer.h"
#include "font.h"
#include "types.h"
#include "actor/ball.h"
#include "actor/paddle.h"
#include "actor/actor.h"

class game_c final{
    SDL_Window* window_{};
    font_t font{};
    drawer_c drawer_{};
    u32 ticks_count_{};
    actors_t actors_{};
public:
    ~game_c() { shutdown(); }
    bool initialize() noexcept;
    void run_loop() noexcept;
    void shutdown() noexcept;

    void process_input() noexcept;
    void update_game() noexcept;
    void generate_output() noexcept;
};



