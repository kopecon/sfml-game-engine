//
// Created by Andrew on 08/12/2025.
//

#ifndef BONK_GAME_STOPPING_HPP
#define BONK_GAME_STOPPING_HPP

#include "../../../Game/Engines/StateMachine/StateBase_new.hpp"
#include "States.hpp"

namespace player {
    class Stopping final : public StateBase_new<States> {
    public:
        explicit Stopping();

        void update() override;

    };
}



#endif //BONK_GAME_STOPPING_HPP