//
// Created by Andrew on 17/11/2025.
//

#ifndef BONK_GAME_ANIMATION_ENGINE_HPP
#define BONK_GAME_ANIMATION_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Animation.hpp"
#include "AnimationSheet.hpp"
#include "../../../../Utils/EnumSet.hpp"
#include "../../../../Utils/utils.hpp"


template<EnumSetConcept AnimationSet>
class AnimationEngine {
    sf::Sprite &target_;
    AnimationSheet animationSheet_;

public:
#pragma region constructors
    explicit AnimationEngine(sf::Sprite &target, const AnimationSheet &animationSheet) :
        target_(target),
        animationSheet_(animationSheet)
        {}
#pragma endregion

    Animation<AnimationSet> *pCurrentAnimation{nullptr};
    std::unordered_map<typename AnimationSet::ID, std::unique_ptr<Animation<AnimationSet>>> animationSet;

    [[nodiscard]] sf::IntRect getCurrentFrame() const {
        auto framePosition = sf::Vector2i(
            hd::multiply(pCurrentAnimation->getFrameIndex(), animationSheet_.frameSize)
        );
        auto frameSize = static_cast<sf::Vector2i>(animationSheet_.frameSize);

        return {framePosition, frameSize};
    }

    void set(const typename AnimationSet::ID &animationID) {
        auto *pNewAnimation = animationSet[animationID].get();
        if (pCurrentAnimation == nullptr) {
            pCurrentAnimation = pNewAnimation;
        }
        else if (pCurrentAnimation != pNewAnimation) {
            // Load desired animation
            pCurrentAnimation = pNewAnimation;
            // Reset the animation
            pCurrentAnimation->reset();
        }
    }

    void add(std::unique_ptr<Animation<AnimationSet>> animation) {
        typename AnimationSet::ID animID = animation->getID();
        animationSet.emplace(animID, std::move(animation));
        if (pCurrentAnimation == nullptr) {
            set(animID);
        }
    }

    void update(const float &dt) const {
        pCurrentAnimation->update(dt);
        target_.setTextureRect(getCurrentFrame());
    }
};
#endif //BONK_GAME_ANIMATION_ENGINE_HPP