//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_ANIMATION_MANAGER_HPP
#define BONK_GAME_ANIMATION_MANAGER_HPP

#include "../../../Includes/Game/Engines/AnimationEngine/AnimationEngine.hpp"
#include "States/StateSet.hpp"


namespace player {
    class Player;

    class AnimationManager final {
        // REFERENCES
        Player &player_;
        // CHARACTERISTICS
        AnimationEngine<StateSet> engine_;

        void selectAnimation_();

        void updateFPS_() const;

    public:
        explicit AnimationManager(Player &player);
        void update();
    };
}




#endif //BONK_GAME_ANIMATION_MANAGER_HPP