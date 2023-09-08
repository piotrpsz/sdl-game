#include "game.h"
#include "drawer.h"
#include <utility>
#include <random>
#include <iostream>
#include "drawer.h"

using namespace std;

f32 random_speed(f32 const start, f32 const end) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distr(start, end);
    return static_cast<f32>(distr(gen));
}

bool game_c::initialize() noexcept {
    if (auto err = SDL_Init(SDL_INIT_VIDEO); err) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    if (window_ = SDL_CreateWindow("My SDL game", WINDOW_WIDTH, WINDOW_HEIGHT, 0); window_ == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    if (drawer_ = drawer_c(window_); !drawer_.ok())
        return false;

    paddle_pos_ = {12.f, WINDOW_HEIGHT / 2.f};
    ball_pos_ = {WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f};

    auto const vx = random_speed(-100.0f, -70.f);
    auto const vy = random_speed(70.f, 100.f);
    ball_velocity_ = {vx, vy};
    cout << "vx: " << vx << ", vy: " << vy << '\n';
//    ball_velocity_ = {-50.f, 90.f};
    return true;
}

void game_c::run_loop() noexcept {
    while (is_running) {
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
                is_running = false;
                break;
        }
    }

    u8 const *state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE])
        is_running = false;

    paddle_direction_ = Direction::Unknown;
    if (state[SDL_SCANCODE_UP])
        paddle_direction_ = Direction::Up;
    if (state[SDL_SCANCODE_DOWN])
        paddle_direction_ = Direction::Down;
}

void game_c::update_game() noexcept {
    auto const deadline = 10;
    // Wait until 16ms has elapsed since last frame
    while (SDL_GetTicks() < (ticks_count_ + deadline));

    // Delta time is the difference in ticks from last frame
    // (converted to seconds)
    auto delta_time = static_cast<f32>(SDL_GetTicks() - ticks_count_ + deadline) / 1000.f;
    if (delta_time > .05f)
        delta_time = .05f;
    ticks_count_ = SDL_GetTicks();

    if (paddle_direction_ == Direction::Up) {
        paddle_pos_.y += -300.f * delta_time;
        if (paddle_pos_.y < (PADDLE_HEIGHT / 2.f + THICKNESS + 1))
            paddle_pos_.y = PADDLE_HEIGHT / 2.f + THICKNESS + 1;
    } else if (paddle_direction_ == Direction::Down) {
        paddle_pos_.y += 300.f * delta_time;
        if (paddle_pos_.y > (WINDOW_HEIGHT - PADDLE_HEIGHT / 2.f - THICKNESS - 1))
            paddle_pos_.y = WINDOW_HEIGHT - PADDLE_HEIGHT / 2.f - THICKNESS - 1;
    }

    // update ball position based on ball velocity
    ball_pos_.x += ball_velocity_.x * delta_time;
    ball_pos_.y += ball_velocity_.y * delta_time;

    //------- horizontal movement of the ball
    if (ball_velocity_.x < 0.f) {
        // The ball moves to the left
        auto diff = paddle_pos_.y - ball_pos_.y;
        diff = (diff > 0.f) ? diff : -diff;
        if (diff > PADDLE_HEIGHT / 2.f) {
            if ((ball_pos_.x - BALL_RADIUS) <= 0) {
                is_running = false;
                return;
            }
        } else if ((ball_pos_.x - BALL_RADIUS) <= (paddle_pos_.x + THICKNESS / 2.0)) {
            // the ball bounces off the paddle
            ball_velocity_.x *= -1.f;
        }
    } else if (ball_velocity_.x > 0.f) {
        // the ball moves to the right
        if ((ball_pos_.x + BALL_RADIUS) > RIGHT_BORDER)
            // the ball bounces off the right wall
            ball_velocity_.x *= -1.f;
    }

    //------- vertical movement of the ball
    if (ball_velocity_.y < 0.f) {
        // the ball moves upwards
        if ((ball_pos_.y - BALL_RADIUS) <= TOP_BORDER)
            //the ball bounces off the upper wall
            ball_velocity_.y *= -1.f;
    } else if (ball_velocity_.y > 0.f) {
        // the ball moves downwards
        if ((ball_pos_.y + BALL_RADIUS) >= BOTTOM_BORDER)
            // the ball bounces off the bottom wall
            ball_velocity_.y *= -1.f;
    }
}

void game_c::generate_output() noexcept {
    drawer_.draw_color({0, 40, 30, 255});
    drawer_.clear();

    //------- draw walls
    drawer_.draw_color({255, 255, 255, 255});
    // draw the top wall
    drawer_.fill_rect({0, 0, WINDOW_WIDTH, THICKNESS});
    // draw the bottom wall
    drawer_.fill_rect({0, WINDOW_HEIGHT - THICKNESS, WINDOW_WIDTH, THICKNESS});
    // draw the right wall
    drawer_.fill_rect({WINDOW_WIDTH - THICKNESS, 0, THICKNESS, WINDOW_WIDTH});

    // draw the paddle paddle
    drawer_.draw_color({255, 0, 0, 255});
    drawer_.fill_rect({paddle_pos_.x - THICKNESS / 2.f, paddle_pos_.y - PADDLE_HEIGHT / 2, THICKNESS, PADDLE_HEIGHT});

    // draw the ball
    drawer_.draw_color({255, 255, 255, 255});
    drawer_.draw_circle({ball_pos_.x, ball_pos_.y}, static_cast<int>(THICKNESS / 2.f));

    drawer_.present();
}

void game_c::shutdown() noexcept {
    drawer_.destroy();
    if (window_)
        SDL_DestroyWindow(window_);
    SDL_Quit();
}
