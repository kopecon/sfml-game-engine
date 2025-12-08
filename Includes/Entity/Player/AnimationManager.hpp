//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_ANIMATION_MANAGER_HPP
#define BONK_GAME_ANIMATION_MANAGER_HPP

#include "../../Game/Engines/AnimationEngine.hpp"

class Player;


class AnimationManager final : public AnimationEngine<player::States> {
public:
    AnimationManager();

    explicit AnimationManager(Player &player);

    Player *pPlayer{nullptr};

    void selectAnimation() const;

    void update() const;
};


#endif //BONK_GAME_ANIMATION_MANAGER_HPP