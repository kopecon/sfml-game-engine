//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_WALKING_HPP
#define BONK_GAME_WALKING_HPP
#include "State.hpp"


class Walking final : public State {
public:
    Walking();
    explicit Walking(Player &player);
    void act() override;
};


#endif //BONK_GAME_WALKING_HPP