//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_STATE_MANAGER_HPP
#define BONK_GAME_STATE_MANAGER_HPP

#include "../../Game/Engines/StateMachine/StateMachine.hpp"


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
        States targetStateID{};  // Usually triggered by the user's input
        std::vector<States> conditions{};  // TODO for now the only condition inside the vector is just the desired state, in the future maybe other conditions would be added.
        StateMachine<StateManager> engine{};

        void update();
    };
}


#endif //BONK_GAME_STATE_MANAGER_HPP