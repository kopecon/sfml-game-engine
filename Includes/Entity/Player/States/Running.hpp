//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_RUNNING_HPP
#define BONK_GAME_RUNNING_HPP
#include "../../../Game/Engines/StateMachine/StateMachine.hpp"

namespace player {
    class Running final : public StateBase<StateManager>{
    public:
        explicit Running(StateManager *stateManager);

        void update() override;

    };
}



#endif //BONK_GAME_RUNNING_HPP