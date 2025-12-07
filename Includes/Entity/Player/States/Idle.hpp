//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_IDLE_HPP
#define BONK_GAME_IDLE_HPP
#include "State.hpp"


class Idle final : public State {
public:
    Idle();

    explicit Idle(Player &player);
    void act() override;
};

#endif //BONK_GAME_IDLE_HPP