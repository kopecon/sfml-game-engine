//
// Created by Andrew on 26/12/2025.
//

#ifndef BONK_GAME_IDLE_NEW_HPP
#define BONK_GAME_IDLE_NEW_HPP

#include "../../../Game/Engines/StateMachine/StateBase_new.hpp"

enum class States;

namespace player {
    class Idle final : public StateBase_new<States> {
    public:
        explicit Idle();

        void update() override;
    };
}

#endif //BONK_GAME_IDLE_NEW_HPP