//
// Created by Piotr Pszczółkowski on 12/09/2023.
//

#include "audio.h"
#include <fmod_studio.hpp>
#include <fmod_common.h>


using namespace std;

bool audio_t::inittialize() {
    // Initialize debug logging
    if (auto err = FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR, FMOD_DEBUG_MODE_TTY); err != FMOD_OK) {
        SDL_Log("Failed to debug initialization: %s", FMOD_ErrorString(err));
        return false;
    }

    // Create FMOD studio system object
    if (auto result = FMOD::Studio::System::create(&system_); result != FMOD_OK) {
        SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
        return false;
    }

    // Initialize FMOD studio system
    if (auto result = system_->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr); result != FMOD_OK) {
        SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
        return false;
    }

    // Save the low-level system pointer
    if (auto result = system_->getCoreSystem(&low_level_system_); result != FMOD_OK) {
        SDL_Log("Failed to obtain FMOD core system: %s", FMOD_ErrorString(result));
        return false;
    }

    return true;
}

void audio_t::shutdown() {

}

bool audio_t::load_bank(string const& name) {
    if (banks_.find(name) != banks_.end())
        return false;

    // try to load bank
    FMOD::Studio::Bank *bank{};
    if (auto result = system_->loadBankFile(name.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank); result != FMOD_OK) {
        SDL_Log("Failed to load bank file: %s", FMOD_ErrorString(result));
        return false;
    }
    banks_.emplace(name, bank);

    if (auto result = bank->loadSampleData(); result != FMOD_OK) {
        SDL_Log("Failed to load sample data of bank: %s", FMOD_ErrorString(result));
        return false;
    }

    // events in the bank
    if (auto events_n = events_number(bank); events_n > 0)
        if (auto vec = events_list(bank, events_n); !vec.empty()) {
            for (auto e: vec)
                if (auto path = get_path(e); path.has_value())
                    events_.emplace(path.value(), e);
        }

    // buses in the bank
    if (auto buses_n = buses_number(bank); buses_n > 0)
        if (auto vec = buses_list(bank, buses_n); !vec.empty()) {
            for (auto b : vec)
                if (auto path = get_path(b); path.has_value())
                    buses_.emplace(name, b);
        }

    return true;
}

void audio_t::unload_bank(const std::string& name) {
    auto const it = banks_.find(name);
    if (it == banks_.end())
        return;

    // events
    if (auto events_n = events_number(it->second); events_n > 0)
        if (auto const vec = events_list(it->second, events_n); !vec.empty()) {
            char event_name[MAX_PATH_LEMGTH];
            for (auto const& e: vec)
                if (e->getPath(event_name, MAX_PATH_LEMGTH, nullptr) == FMOD_OK)
                    if (auto eti = events_.find(event_name); eti != events_.end())
                        events_.erase(eti);

        }

    // buses
    if (auto buses_n = buses_number(it->second); buses_n > 0)
        if (auto const buses = buses_list(it->second, buses_n); !buses.empty()) {
            char name[MAX_PATH_LEMGTH];
            for (auto const& b: buses)
                if (b->getPath(name, MAX_PATH_LEMGTH, nullptr) == FMOD_OK)
                    if (auto bit = buses_.find(name); bit != buses_.end())
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