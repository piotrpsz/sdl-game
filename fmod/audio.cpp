//
// Created by Piotr Pszczółkowski on 12/09/2023.
//

#include "audio.h"
#include <fmod_studio.hpp>
#include <fmod_common.h>


using namespace std;

/// Initialization of FMOD system.
bool audio_t::initialize() {
    // Initialize debug logging
    if (auto err = FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR, FMOD_DEBUG_MODE_TTY); err != FMOD_OK) {
        SDL_Log("Failed to debug initialization: %s", FMOD_ErrorString(err));
        return false;
    }

    // Create FMOD studio system object
    if (auto err = FMOD::Studio::System::create(&system_); err != FMOD_OK) {
        SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(err));
        return false;
    }

    // Initialize FMOD studio system
    if (auto err = system_->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr); err != FMOD_OK) {
        SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(err));
        return false;
    }

    // Save the low-level system pointer
    if (auto err = system_->getCoreSystem(&low_level_system_); err != FMOD_OK) {
        SDL_Log("Failed to obtain FMOD core system: %s", FMOD_ErrorString(err));
        return false;
    }

    return true;
}

/// Frees resources of FMOD system.
void audio_t::shutdown() {
    unload_all_banks();
    if (system_)
        if (auto err = system_->release(); err != FMOD_OK)
            SDL_Log("Failed to release: %s", FMOD_ErrorString(err));
}

/// Loads specified bank.
void audio_t::load_bank(string const& path) noexcept {
    if (banks_.find(path) != banks_.end())
        return;

    // try to load bank
    FMOD::Studio::Bank *bank{};
    if (auto err = system_->loadBankFile(path.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank); err != FMOD_OK) {
        SDL_Log("Failed to load bank file: %s", FMOD_ErrorString(err));
        return;
    }
    banks_.emplace(path, bank);

    if (auto err = bank->loadSampleData(); err != FMOD_OK) {
        SDL_Log("Failed to load sample data of bank: %s", FMOD_ErrorString(err));
        return;
    }

    // events in the bank
    if (auto events_n = events_number(bank); events_n > 0)
        if (auto vec = events_list(bank, events_n); !vec.empty()) {
            for (auto e: vec)
                if (auto name = get_path(e); name.has_value())
                    events_.emplace(name.value(), e);
        }

    // buses in the bank
    if (auto buses_n = buses_number(bank); buses_n > 0)
        if (auto vec = buses_list(bank, buses_n); !vec.empty()) {
            for (auto b: vec)
                if (auto name = get_path(b); name.has_value())
                    buses_.emplace(name.value(), b);
        }
}

/// Releases data of specified bank
void audio_t::unload_bank(const std::string& path) {
    auto const it = banks_.find(path);
    if (it == banks_.end())
        return;

    // events
    if (auto events_n = events_number(it->second); events_n > 0)
        if (auto const vec = events_list(it->second, events_n); !vec.empty()) {
            for (auto const& e: vec)
                if (auto name = get_path(e); name.has_value())
                    if (auto eti = events_.find(name.value()); eti != events_.end())
                        events_.erase(eti);

        }

    // buses
    if (auto buses_n = buses_number(it->second); buses_n > 0)
        if (auto const buses = buses_list(it->second, buses_n); !buses.empty()) {
            for (auto const& b: buses)
                if (auto name = get_path(b); name.has_value())
                    if (auto bit = buses_.find(name.value()); bit != buses_.end())
                        buses_.erase(bit);
        }

    it->second->unloadSampleData();
    it->second->unload();
    banks_.erase(it);
}

void audio_t::unload_all_banks() {
    for (auto const& it: banks_) {
        it.second->unloadSampleData();
        it.second->unload();
    }
    banks_.clear();
    events_.clear();
}

FMOD::Studio::EventInstance* audio_t::event_instance(uint const id) const noexcept {
    FMOD::Studio::EventInstance* event{};
    if (auto it = event_instances_.find(id); it != event_instances_.end())
        event = it->second;
    return event;
}
