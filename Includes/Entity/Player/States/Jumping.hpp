//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_JUMPING_HPP
#define BONK_GAME_JUMPING_HPP

#include "../../../Game/Engines/StateMachine/StateBase_new.hpp"
#include "States.hpp"

namespace player {
    class Jumping final : public StateBase_new<States> {
    public:

        explicit Jumping();

        void onEnter() override;

        void onExit() override;

        void update() override;

    };
}



#endif //BONK_GAME_JUMPING_HPP