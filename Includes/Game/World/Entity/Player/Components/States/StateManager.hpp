//
// Created by Andrew on 29/12/2025.
//

#ifndef BONK_GAME_STATE_MANAGER_HPP
#define BONK_GAME_STATE_MANAGER_HPP
#include "StateSet.hpp"
#include "Game/Engines/StateMachine/StateMachine.hpp"


namespace player {
    class Player;

    class StateManager : public StateMachine<StateSet> {
    public:
        explicit StateManager(Player &player);
    };
}


#endif //BONK_GAME_STATE_MANAGER_HPP
