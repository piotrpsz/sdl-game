//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//

#include "ball.h"
#include "actor.h"
#include <iostream>
using namespace std;

void ball_t::output(drawer_t const& drawer) const noexcept {
    drawer.draw_color({255, 255, 0, 255});
    drawer.draw_filled_circle(position_.x, position_.y, BALL_RADIUS);

//    rect_t rect{position_.x - BALL_RADIUS, position_.y-BALL_RADIUS, BALL_DIAMETER, BALL_DIAMETER};
//    drawer.render_texture(texture_, rect);
}

void ball_t::update(f32 delta_time, actors_t& actors) noexcept {
    position_.x += velocity_.x * delta_time;
    position_.y += velocity_.y * delta_time;

    if (velocity_.x < 0.f) {
        // the ball moves to the left
        auto const paddle = actors.get<paddle_t>(); // get the paddle
        auto diff = paddle->pos().y - position_.y;
        diff = (diff > 0.f) ? diff : -diff;
        if (diff > paddle_t::HEIGHT/2.f) {
            if ((position_.x - BALL_RADIUS) <= 0) {
                shared::is_running = false;
                return;
            }
        }
        else if ((position_.x - BALL_RADIUS) <= (paddle->pos().x + paddle_t::WIDTH/2.f)) {
            shared::scores++;
            velocity_.x *= -1.f;
        }
    }
    else if (velocity_.x > 0.f) {
        if ((position_.x + BALL_RADIUS) > shared::RIGHT_BORDER)
            // the ball bounces off the right wall
            velocity_.x *= -1.f;
    }

    if (velocity_.y < 0.f) {
        // the ball moves upwards
        if ((position_.y - BALL_RADIUS) <= shared::TOP_BORDER)
            //the ball bounces off the upper wall
            velocity_.y *= -1.f;
    } else if (velocity_.y > 0.f) {
        // the ball moves downwards
        if ((position_.y + BALL_RADIUS) >= shared::BOTTOM_BORDER)
            // the ball bounces off the bottom wall
            velocity_.y *= -1.f;
    }
}

ostream& operator<<(ostream& s, ball_t const& b) {
    s << "ball[pos:(" << b.position_.x << "," << b.position_.y << ") v:(" << b.velocity_.x << "," <<  b.velocity_.y << ")]\n";
    return s;
}
