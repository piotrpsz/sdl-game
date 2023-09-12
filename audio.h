#ifndef SDL_GAME_AUDIO_H
#define SDL_GAME_AUDIO_H

#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <fmod_errors.h>
#include <SDL.h>
#include <string>
#include <unordered_map>
#include <optional>

class audio_t {
    constexpr static int MAX_PATH_LEMGTH = 512;
    FMOD::Studio::System *system_{};
    FMOD::System *low_level_system_{};
    std::unordered_map<std::string, FMOD::Studio::Bank *> banks_;
    std::unordered_map<std::string, FMOD::Studio::EventDescription *> events_;
    std::unordered_map<std::string, FMOD::Studio::Bus *> buses_;

    class game_c *game_;

public:
    audio_t(class game_c *game) : game_{game} {
    }

    ~audio_t() = default;

    bool inittialize();

    void shutdown();

    bool load_bank(std::string const& name);

    void unload_bank(std::string const& name);
    void unload_all_banks();

    std::optional<std::string> get_path(auto* o) {
        char name[MAX_PATH_LEMGTH];
        if (auto err = o->getPath(name, MAX_PATH_LEMGTH, nullptr); err != FMOD_OK) {
            SDL_Log("Failed to get path: %s", FMOD_ErrorString(err));
            return {};
        }
        return std::string{name};
    }

    int events_number(FMOD::Studio::Bank *const bank) const noexcept {
        int n{};
        if (bank)
            if (auto err = bank->getEventCount(&n); err != FMOD_OK) {
                SDL_Log("Failed to get events count: %s", FMOD_ErrorString(err));
                return {};
            }
        return n;
    }

    static int buses_number(FMOD::Studio::Bank *const bank) noexcept {
        int n{};
        if (bank)
            if (auto err = bank->getBusCount(&n); err != FMOD_OK) {
                SDL_Log("Failed to get buses count: %s", FMOD_ErrorString(err));
                return {};
            }
        return n;
    }

    static std::vector<FMOD::Studio::EventDescription *> events_list(FMOD::Studio::Bank *const bank, int n) {
        std::vector<FMOD::Studio::EventDescription *> vec(n);
        if (auto err = bank->getEventList(vec.data(), n, &n); err != FMOD_OK) {
            SDL_Log("Failed to get events list: %s", FMOD_ErrorString(err));
            return {};
        }
        return vec;
    }

    std::vector<FMOD::Studio::Bus *> buses_list(FMOD::Studio::Bank *const bank, int n) {
        std::vector<FMOD::Studio::Bus *> vec(n);
        if (auto err = bank->getBusList(vec.data(), n, &n); err != FMOD_OK) {
            SDL_Log("Failed to get events buses: %s", FMOD_ErrorString(err));
        }

        return vec;
    }
};


#endif //SDL_GAME_AUDIO_H
