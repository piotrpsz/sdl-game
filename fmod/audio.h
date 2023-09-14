#ifndef SDL_GAME_AUDIO_H
#define SDL_GAME_AUDIO_H

#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <SDL.h>
#include <string>
#include <unordered_map>
#include <optional>
#include "../types.h"

class audio_t {
    using bus_t = FMOD::Studio::Bus;
    using bank_t = FMOD::Studio::Bank;
    using event_instance_t = FMOD::Studio::EventInstance;
    using event_description_t = FMOD::Studio::EventDescription;

    constexpr static int MAX_PATH_LEMGTH = 512;

    FMOD::Studio::System *system_{};
    FMOD::System *low_level_system_{};
    std::unordered_map<std::string, bus_t *> buses_{};
    std::unordered_map<std::string, bank_t*> banks_{};
    std::unordered_map<std::string, event_description_t*> events_{};
    std::unordered_map<uint, event_instance_t*> event_instances_{};

    class game_c *game_;

public:
    explicit audio_t(class game_c *game) : game_{game} {}
    ~audio_t() = default;

    bool initialize();
    void shutdown();
    void load_bank(std::string const& path) noexcept;
    void unload_bank(std::string const& path);
    void unload_all_banks();

private:
    std::optional<std::string> get_path(auto* o) {
        char name[MAX_PATH_LEMGTH];
        if (auto err = o->getPath(name, MAX_PATH_LEMGTH, nullptr)) {
            SDL_Log("Failed to get path: %s", FMOD_ErrorString(err));
            return {};
        }
        return std::string{name};
    }

    static int events_number(bank_t* const bank) noexcept {
        int n{};
        if (bank)
            if (auto err = bank->getEventCount(&n)) {
                SDL_Log("Failed to get events count: %s", FMOD_ErrorString(err));
                return {};
            }
        return n;
    }

    static int buses_number(bank_t* const bank) noexcept {
        int n{};
        if (bank)
            if (auto err = bank->getBusCount(&n)) {
                SDL_Log("Failed to get buses count: %s", FMOD_ErrorString(err));
                return {};
            }
        return n;
    }

    static std::vector<event_description_t*> events_list(bank_t* const bank, int n) {
        std::vector<event_description_t*> vec(n);
        if (auto err = bank->getEventList(vec.data(), n, &n)) {
            SDL_Log("Failed to get events list: %s", FMOD_ErrorString(err));
            return {};
        }
        return vec;
    }

    std::vector<bus_t*> buses_list(FMOD::Studio::Bank *const bank, int n) {
        std::vector<bus_t*> vec(n);
        if (auto err = bank->getBusList(vec.data(), n, &n)) {
            SDL_Log("Failed to get events buses: %s", FMOD_ErrorString(err));
            return {};
        }
        return vec;
    }

protected:
    friend class sound_event_t;
    FMOD::Studio::EventInstance* event_instance(uint id) const noexcept;
};


#endif //SDL_GAME_AUDIO_H
