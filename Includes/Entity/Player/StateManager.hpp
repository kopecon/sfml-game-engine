//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_STATE_MANAGER_HPP
#define BONK_GAME_STATE_MANAGER_HPP

#include "../../Game/Engines/StateMachine.hpp"


class Player;


namespace player {
    class StateManager {
    public:
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

        StateManager();
        explicit StateManager(Player &player);

        Player *pPlayer{nullptr};
        StateMachine<StateManager> engine{};

        void update() {
            engine.update();
        }
    };
}


#endif //BONK_GAME_STATE_MANAGER_HPP