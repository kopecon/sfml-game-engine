//
// Created by Andrew on 08/12/2025.
//

#ifndef BONK_GAME_STOPPING_HPP
#define BONK_GAME_STOPPING_HPP
#include "../../../Game/Engines/StateMachine/StateMachine.hpp"

namespace player {
    class Stopping final : public StateBase<StateManager> {
    public:
        explicit Stopping(StateManager *stateManager);

        void update() override;

    };
}



#endif //BONK_GAME_STOPPING_HPP