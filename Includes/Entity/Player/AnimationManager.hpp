//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_ANIMATION_MANAGER_HPP
#define BONK_GAME_ANIMATION_MANAGER_HPP

#include "../../Game/Engines/AnimationEngine.hpp"
#include "States/StateSet.hpp"


namespace player {
    class Player;

    class AnimationManager final {
    public:
        AnimationManager();

        explicit AnimationManager(Player &player);

        Player *pPlayer{nullptr};
        AnimationEngine<StateSet::ID> engine{};

        void selectAnimation();

        void update();
    };
}




#endif //BONK_GAME_ANIMATION_MANAGER_HPP