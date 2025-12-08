//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_IDLE_HPP
#define BONK_GAME_IDLE_HPP

#include "State.hpp"


class Idle final : public State {
public:
    explicit Idle(StateManager *stateManager);

    void act() override;

    void exit() override;
};

#endif //BONK_GAME_IDLE_HPP