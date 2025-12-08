//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_JUMPING_HPP
#define BONK_GAME_JUMPING_HPP
#include "../../../Game/Engines/StateMachineEngine.hpp"


class Jumping final : public State<player::StateManager, player::States> {
public:

    explicit Jumping(player::StateManager *stateManager);

    bool inAir{false};

    void act() override;

    void exit() override;
};


#endif //BONK_GAME_JUMPING_HPP