//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_JUMPING_HPP
#define BONK_GAME_JUMPING_HPP
#include "State.hpp"


class Jumping final : public State {
public:
    explicit Jumping();

    explicit Jumping(StateManager *stateManager);

    bool inAir{false};

    void enter() override;

    void act() override;

    void exit(const StateManager::States &condition) override;
};


#endif //BONK_GAME_JUMPING_HPP