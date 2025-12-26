//
// Created by Andrew on 26/12/2025.
//

#ifndef BONK_GAME_STATES_HPP
#define BONK_GAME_STATES_HPP

namespace player {
    enum class States {
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
    };
}

#endif //BONK_GAME_STATES_HPP