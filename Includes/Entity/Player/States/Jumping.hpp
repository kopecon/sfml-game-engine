//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_JUMPING_HPP
#define BONK_GAME_JUMPING_HPP
#include "State.hpp"


class Jumping final : public State {
public:
    Jumping();

    explicit Jumping(Player &player);

    void act() override;;
};


#endif //BONK_GAME_JUMPING_HPP