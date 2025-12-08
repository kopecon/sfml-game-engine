//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_WALKING_HPP
#define BONK_GAME_WALKING_HPP
#include "../../../Game/Engines/StateMachineEngine.hpp"


class Walking final : public State<player::StateManager, player::States> {
public:
    explicit Walking(player::StateManager *stateManager);

    void act() override;

    void exit() override;
};


#endif //BONK_GAME_WALKING_HPP