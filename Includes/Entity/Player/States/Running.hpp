//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_RUNNING_HPP
#define BONK_GAME_RUNNING_HPP

#include "../../../Game/Engines/StateMachine/StateBase_new.hpp"
#include "States.hpp"


namespace player {
    class Running final : public StateBase_new<States>{
    public:
        explicit Running();

        void update() override;

    };
}



#endif //BONK_GAME_RUNNING_HPP