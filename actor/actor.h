//
// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
// E-mail: piotr@beesoft.pl
//
#ifndef SDL_GAME_ACTOR_H
#define SDL_GAME_ACTOR_H

#include "ball.h"
#include "paddle.h"
#include "wall.h"
#include "label.h"
#include <variant>
#include <vector>
#include <iterator>

using actor_t = std::variant<ball_t, paddle_t, wall_t, label_t>;

class actors_t final {
    std::vector<actor_t> data_{};
public:
    void reserve(size_t const n) noexcept {
        data_.reserve(n);
    }
    void push_back(actor_t actor) noexcept { data_.push_back(actor); }
    void emplace_back(actor_t actor) noexcept { data_.emplace_back(actor); }
    [[nodiscard]] size_t size() const noexcept { return data_.size(); }

public:
    void input(u8 const *state) noexcept;
    void update(f32 delta_time) noexcept;
    void output(drawer_t const& drawer) const noexcept;

    using iterator = std::vector<actor_t>::iterator;
    using const_iterator = std::vector<actor_t>::const_iterator;
    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }
    [[nodiscard]] const_iterator cbegin() const { return data_.cbegin(); }
    [[nodiscard]] const_iterator cend() const { return data_.cend(); }

    template<class T> T const* get() noexcept {
        for (auto& it : data_)
            if (auto const * const a = get_if<T>(&it))
                return a;
        return nullptr;
    }
};

#endif //SDL_GAME_ACTOR_H
