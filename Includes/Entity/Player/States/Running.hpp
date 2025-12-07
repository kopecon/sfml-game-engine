//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_RUNNING_HPP
#define BONK_GAME_RUNNING_HPP
#include "State.hpp"


class Running final : public State{
public:
    Running();

    explicit Running(Player &player);

    void act() override;
};


#endif //BONK_GAME_RUNNING_HPP