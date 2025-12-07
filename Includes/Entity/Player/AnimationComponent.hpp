//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_ANIMATION_COMPONENT_HPP
#define BONK_GAME_ANIMATION_COMPONENT_HPP

#include "../Animations.hpp"

class Player;


class AnimationComponent : public Animations {
public:
    AnimationComponent();

    explicit AnimationComponent(Player &player);

    Player *pPlayer{nullptr};

    void selectAnimation() const;;
};


#endif //BONK_GAME_ANIMATION_COMPONENT_HPP