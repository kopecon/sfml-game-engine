//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_IDLE_HPP
#define BONK_GAME_IDLE_HPP

#include "../../../Game/Engines/StateMachine.hpp"

namespace player {
    class Idle final : public State<StateManager> {
    public:
        explicit Idle(StateManager *stateManager);

        void update() override;

        StateManager::States next(const std::vector<StateManager::States> &conditions) override;

    };
}


#endif //BONK_GAME_IDLE_HPP