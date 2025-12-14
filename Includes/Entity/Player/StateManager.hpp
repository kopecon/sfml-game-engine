//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_STATE_MANAGER_HPP
#define BONK_GAME_STATE_MANAGER_HPP
#include <memory>

#include "../../Game/Engines/StateMachineEngine.hpp"


class Player;

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

    class StateManager : public StateMachineEngine<StateManager, States> {
    public:
        StateManager();
        explicit StateManager(Player &player);

        Player *pPlayer{nullptr};
    };
}


#endif //BONK_GAME_STATE_MANAGER_HPP