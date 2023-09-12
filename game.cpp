//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#include "game.h"
#include "drawer.h"
#include "shared.h"
#include "actor/label.h"

using namespace std;

bool game_c::initialize() noexcept {
    if (auto err = SDL_Init(SDL_INIT_VIDEO); err) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    int n{};
    SDL_GetDisplays(&n);
    int x{}, y{};
    if (n > 1) {
        SDL_Rect r{};
        SDL_GetDisplayBounds(2, &r);
        x = r.x + (r.w - shared::WINDOW_WIDTH)/2;
        y = r.y + (r.h - shared::WINDOW_HEIGHT)/2;
    } else {
        SDL_Rect r{};
        SDL_GetDisplayBounds(1, &r);
        x = r.x + (r.w - shared::WINDOW_WIDTH)/2;
        y = r.y + (r.h - shared::WINDOW_HEIGHT)/2;
    }

    if (window_ = SDL_CreateWindow("My SDL game", shared::WINDOW_WIDTH, shared::WINDOW_HEIGHT, 0); window_ == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    SDL_SetWindowPosition(window_, x, y);

    if (drawer_ = drawer_t(window_); !drawer_.ok())
        return false;

    IMG_Init(IMG_INIT_PNG);

    if (TTF_Init() != 0) {
        SDL_Log("Can't init TTF library: %s", SDL_GetError());
        return false;
    }

    auto ball = ball_t({shared::WINDOW_WIDTH / 2.f, shared::WINDOW_HEIGHT / 2.f}, shared::texture_from_file(drawer_(), "../assets/tennis.png"));
    auto paddle = paddle_t({6.f, shared::WINDOW_HEIGHT / 2.f}, ActorType::PADDLE_LEFT);
    auto wall_top = wall_t({0, 0, shared::WINDOW_WIDTH, shared::THICKNESS}, ActorType::WALL_TOP);
    auto wall_bottom = wall_t({0, shared::WINDOW_HEIGHT - shared::THICKNESS, shared::WINDOW_WIDTH, shared::THICKNESS}, ActorType::WALL_BOTTOM);
    auto wall_right = wall_t({shared::WINDOW_WIDTH - shared::THICKNESS, 0, shared::THICKNESS, shared::WINDOW_WIDTH}, ActorType::WALL_RIGHT);
    auto label = label_t("Scores: ", {2, 2}, 14, &shared::scores);

    actors_.push_back(ball);
    actors_.push_back(paddle);
    actors_.push_back(wall_top);
    actors_.push_back(wall_bottom);
    actors_.push_back(wall_right);
    actors_.push_back(label);

    return true;
}

void game_c::run_loop() noexcept {
    while (shared::is_running) {
        process_input();
        update_game();
        generate_output();
    }
}

void game_c::process_input() noexcept {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                shared::is_running = false;
                break;
        }
    }

    u8 const *state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE])
        shared::is_running = false;

    actors_.input(state);
}

void game_c::update_game() noexcept {
    auto const deadline = 16;
    // Wait until 16ms has elapsed since last frame
    while (SDL_GetTicks() < (ticks_count_ + deadline));

    // Delta time is the difference in ticks from last frame (in seconds)
    auto delta_time = static_cast<f32>(SDL_GetTicks() - ticks_count_ + deadline) / 1000.f;
    if (delta_time > .05f) delta_time = .05f;
    ticks_count_ = SDL_GetTicks();

    actors_.update(delta_time);
}

void game_c::generate_output() noexcept {
    drawer_.draw_color({20, 40, 60, 255});

    drawer_.clear();
    actors_.output(drawer_);
    drawer_.present();
}

void game_c::shutdown() noexcept {
    drawer_.destroy();
    if (window_)
        SDL_DestroyWindow(window_);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
