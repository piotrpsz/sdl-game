#ifndef SDL_GAME_SOUND_EVENT_H
#define SDL_GAME_SOUND_EVENT_H

#include "../types.h"
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <string>

class sound_event_t {
    class audio_t* system_{};
    uint id_{};
public:
    sound_event_t() = default;
    [[nodiscard]] bool valid() const noexcept;
    void restart() const noexcept;
    void stop(bool stop_mode = true) const noexcept;
    // setters
    void paused(bool pause) const noexcept;
    void volume(f32 value) const noexcept;
    void pitch(f32 value) const noexcept;
    void parameter(std::string const& name, f32 value) const noexcept;
    // getters
    [[nodiscard]] bool paused() const noexcept;
    [[nodiscard]] f32 volume() const noexcept;
    [[nodiscard]] f32 pitch() const noexcept;
    [[nodiscard]] f32 parameter(std::string const& name) const noexcept;
    // positional
    bool is3D() const noexcept;
    void set3D_attr(matrix4_t const& transormation) const noexcept;
protected:
    friend class audio_t;
    sound_event_t(class audio_t* system, uint id) : system_{system}, id_{id} {}
};


#endif //SDL_GAME_SOUND_EVENT_H
