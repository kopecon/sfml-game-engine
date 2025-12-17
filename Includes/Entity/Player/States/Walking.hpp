//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_WALKING_HPP
#define BONK_GAME_WALKING_HPP
#include "../../../Game/Engines/StateMachine.hpp"

namespace player {
    class Walking final : public State<StateManager> {
    public:
        explicit Walking(StateManager *stateManager);

        void update() override;

        StateManager::States next(const std::vector<StateManager::States> &conditions) override;
    };
}



#endif //BONK_GAME_WALKING_HPP