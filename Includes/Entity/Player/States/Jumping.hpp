//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_JUMPING_HPP
#define BONK_GAME_JUMPING_HPP
#include "../../../Game/Engines/StateMachine/StateMachine.hpp"

namespace player {
    class Jumping final : public StateBase<StateManager> {
    public:

        explicit Jumping(StateManager *pManager);

        bool inAir{false};

        void update() override;
    };
}



#endif //BONK_GAME_JUMPING_HPP