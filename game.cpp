#include "game.h"
#include "drawer.h"
#include <random>
#include <iostream>
#include <format>
#include <cstdio>
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


    int n{};
    auto _ = SDL_GetDisplays(&n);
    int x{}, y{};
    if (n > 1) {
        SDL_Rect r{};
        SDL_GetDisplayBounds(2, &r);
        x = r.x + (r.w - WINDOW_WIDTH)/2;
        y = r.y + (r.h - WINDOW_HEIGHT)/2;
    } else {
        SDL_Rect r{};
        SDL_GetDisplayBounds(1, &r);
        x = r.x + (r.w - WINDOW_WIDTH)/2;
        y = r.y + (r.h - WINDOW_HEIGHT)/2;
    }

    if (window_ = SDL_CreateWindow("My SDL game", WINDOW_WIDTH, WINDOW_HEIGHT, 0); window_ == nullptr) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    SDL_SetWindowPosition(window_, x, y);

    if (drawer_ = drawer_c(window_); !drawer_.ok())
        return false;

    IMG_Init(IMG_INIT_PNG);

    if (TTF_Init() != 0) {
        SDL_Log("Can't init TTF library: %s", SDL_GetError());
        return false;
    }
    font.load("/Users/piotr/Projects/cpp/sdl-game/assets/Carlito-Regular.ttf");
//    font.load("/System/Library/Fonts/Helvetica.ttc");

    auto surface = IMG_Load("../assets/tennis.png");
    if (surface == nullptr) {

        SDL_Log("Failed to load texture file: %s", SDL_GetError());
        return false;
    }
    auto texture = SDL_CreateTextureFromSurface(drawer_.renderer(), surface);
    if (texture == nullptr) {
        SDL_Log("Failed to convert surface to texture: %s", SDL_GetError());
        return false;
    }
//    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_BEST);

    SDL_DestroySurface(surface);
    ball_ = texture;


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
    auto const deadline = 16;
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
            scores_ += 1;
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
//    drawer_.draw_color({100, 100, 100, 255});
    drawer_.draw_color({20, 40, 60, 255});
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

    {
        char buffer[128];
        snprintf(buffer, 128, "Scores: %d", scores_);
        string text{buffer};
        auto const size = 20;
        if (auto const geometry = font.text_geometry(text, size)) {
            auto const [w, h] = *geometry;
            rect_t const output_rect{2, THICKNESS + 2, w, h};
            if (auto const texture = font.render_text(drawer_.renderer(), text, size, {0, 255, 0, 255}))

                SDL_RenderTexture(drawer_.renderer(), *texture, nullptr, &output_rect);
        }
    }

    // draw the ball
//    drawer_.draw_color({255, 255, 255, 255});
//    drawer_.draw_circle({ball_pos_.x, ball_pos_.y}, static_cast<int>(THICKNESS / 2.f));
    rect_t r{ball_pos_.x - BALL_RADIUS/2.f, ball_pos_.y-BALL_RADIUS/2.f, 2.f * BALL_RADIUS, 2.f * BALL_RADIUS};
    if (auto retv = SDL_RenderTexture(drawer_.renderer(), ball_, nullptr, &r); retv)
        SDL_Log("Failed to render texture: %s", SDL_GetError());

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
