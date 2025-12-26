//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_ANIMATION_MANAGER_HPP
#define BONK_GAME_ANIMATION_MANAGER_HPP

#include "../../Game/Engines/AnimationEngine.hpp"
#include "States/States.hpp"

class Player;

namespace player {
    class AnimationManager final {
    public:
        AnimationManager();

        explicit AnimationManager(Player &player);

        Player *pPlayer{nullptr};
        AnimationEngine<States> engine{};

        void selectAnimation() const;

        void update() const;
    };
}




#endif //BONK_GAME_ANIMATION_MANAGER_HPP