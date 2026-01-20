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
        AnimationEngine &animator_;

        template<EnumSetConcept AnimationSet, typename... Args>
        void addAnimation(const typename AnimationSet::ID &id, Args&&... args) {
            auto animation = std::make_unique<Animation>(
                static_cast<animation_id>(id), args...
            );
            animator_.add(std::move(animation));
        }

        template<EnumSetConcept AnimationSet>
        void setAnimation(const typename AnimationSet::ID &id) {
            animator_.set(static_cast<animation_id>(id));
        }

        void selectAnimation_();

        void updateFPS_() const;

    public:
        explicit AnimationManager(Player &player);
        void update();
    };
}




#endif //BONK_GAME_ANIMATION_MANAGER_HPP