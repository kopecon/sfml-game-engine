//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_JUMPING_HPP
#define BONK_GAME_JUMPING_HPP
#include "../../../Game/Engines/StateMachine.hpp"

namespace player {
    class Jumping final : public State<StateManager> {
    public:

        explicit Jumping(StateManager *stateManager);

        bool inAir{false};

        void update() override;

        StateManager::States next(const std::vector<StateManager::States> &conditions) override;

    };
}



#endif //BONK_GAME_JUMPING_HPP