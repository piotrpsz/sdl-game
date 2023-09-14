//
// Created by Piotr Pszczółkowski on 12/09/2023.
//

#include "sound_event.h"
#include "audio.h"
#include "../math/math.h"
using namespace std;

bool sound_event_t::valid() const noexcept {
    return (system_ != nullptr) && (system_->event_instance(id_));
}

void sound_event_t::restart() const noexcept {
    if (system_)
        if (auto e = system_->event_instance(id_))
            e->start();
}

void sound_event_t::stop(bool const stop_mode) const noexcept {
    if (system_)
        if (auto e = system_->event_instance(id_))
            e->stop(stop_mode ? FMOD_STUDIO_STOP_ALLOWFADEOUT : FMOD_STUDIO_STOP_IMMEDIATE);
}

void sound_event_t::paused(bool pause) const noexcept {
    if (system_)
        if (auto e = system_->event_instance(id_))
            e->setPaused(pause);
}

void sound_event_t::volume(f32 value) const noexcept {
    if (system_)
        if (auto e = system_->event_instance(id_))
            e->setVolume(value);
}

void sound_event_t::pitch(f32 value) const noexcept {
    if (system_)
        if (auto e = system_->event_instance(id_))
            e->setPitch(value);
}

void sound_event_t::parameter(std::string const& name, f32 value) const noexcept {
    if (system_)
        if (auto e = system_->event_instance(id_))
            e->setParameterByName(name.c_str(), value);
}

bool sound_event_t::paused() const noexcept {
    bool v{};
    if (system_)
        if (auto e = system_->event_instance(id_))
            e->getPaused(&v);
    return v;
}

f32 sound_event_t::volume() const noexcept {
    f32 v{};
    if (system_)
        if (auto e = system_->event_instance(id_))
            e->getVolume(&v);
    return v;
}

f32 sound_event_t::pitch() const noexcept {
    f32 v{};
    if (system_)
        if (auto e = system_->event_instance(id_))
            e->getPitch(&v);
    return v;
}

f32 sound_event_t::parameter(std::string const& name) const noexcept {
    f32 v{};
    if (system_)
        if (auto e = system_->event_instance(id_))
            e->getParameterByName(name.c_str(), &v);
    return v;
}

bool sound_event_t::is3D() const noexcept {
    bool v{};
    if (system_)
        if (auto e = system_->event_instance(id_)) {
            FMOD::Studio::EventDescription* ed{};
            if (auto err = e->getDescription(&ed); err != FMOD_OK) {
                SDL_Log("sound_event::is3D(1): %s", FMOD_ErrorString(err));
                return false;
            }
            if (ed) {
                if (auto err = ed->is3D(&v); err != FMOD_OK) {
                    SDL_Log("sound_event::is3D(2): %s", FMOD_ErrorString(err));
                    return false;
                }
            }
        }
    return v;
}

FMOD_VECTOR vec2fmod(vec3_t in ) noexcept{

}

void sound_event_t::set3D_attr(matrix4_t const& transormation) const noexcept {

}
