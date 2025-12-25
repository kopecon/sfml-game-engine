//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_WALKING_HPP
#define BONK_GAME_WALKING_HPP
#include "../../../Game/Engines/StateMachine/StateMachine.hpp"

namespace player {
    class Walking final : public StateBase<StateManager> {
    public:
        explicit Walking(StateManager *stateManager);

        void update() override;

    };
}



#endif //BONK_GAME_WALKING_HPP