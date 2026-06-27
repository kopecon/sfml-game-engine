#ifndef BONK_GAME_DEFAULT_STATES_HPP
#define BONK_GAME_DEFAULT_STATES_HPP

#include "Utils/EnumSet.hpp"


namespace player {
    struct DefaultStateSet;
}

template<>
struct EnumSetTraits<player::DefaultStateSet> {
    enum class Enum {
        NONE = -1,
        IDLE,
        WINKING,
        WALKING,
        RUNNING,
        CROUCHING,
        JUMPING,
        DISAPPEARING,
        DYING,
        ATTACKING,
        BRAKING,
        STOPPING,
        CONCENTRATING,
    };

    static std::string_view name(const Enum &state) {
        using enum Enum;
        switch (state) {
            case NONE: return "NONE";
            case IDLE: return "IDLE";
            case WINKING: return "WINKING";
            case WALKING: return "WALKING";
            case RUNNING: return "RUNNING";
            case CROUCHING: return "CROUCHING";
            case JUMPING: return "JUMPING";
            case DISAPPEARING: return "DISAPPEARING";
            case DYING: return "DYING";
            case ATTACKING: return "ATTACKING";
            case BRAKING: return "BRAKING";
            case STOPPING: return "STOPPING";
            case CONCENTRATING: return "CONCENTRATING";
            default: return "UNKNOWN";
        }
    }
};

namespace player {
    struct DefaultStateSet : EnumSet<DefaultStateSet> {
    };
}


#endif //BONK_GAME_DEFAULT_STATES_HPP
