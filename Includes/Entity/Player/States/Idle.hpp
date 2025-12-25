//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_IDLE_HPP
#define BONK_GAME_IDLE_HPP

#include "../../../Game/Engines/StateMachine/StateMachine.hpp"

namespace player {
    class Idle final : public StateBase<StateManager> {
    public:
        explicit Idle(StateManager *stateManager);

        void update() override;

    };
}


#endif //BONK_GAME_IDLE_HPP