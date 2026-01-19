//
// Created by Andrew on 17/11/2025.
//

#ifndef BONK_GAME_ANIMATION_ENGINE_HPP
#define BONK_GAME_ANIMATION_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Animation.hpp"
#include "AnimationSheet.hpp"
#include "../../../../Utils/utils.hpp"


class AnimationEngine {
    sf::Sprite &target_;
    AnimationSheet animationSheet_;
    Animation *pCurrentAnimation{nullptr};
    std::unordered_map<animation_id, std::unique_ptr<Animation>> animations;

public:
#pragma region constructors
    explicit AnimationEngine(sf::Sprite &target, const AnimationSheet &animationSheet) :
        target_(target),
        animationSheet_(animationSheet)
        {}
#pragma endregion

    [[nodiscard]] sf::IntRect getCurrentFrame() const {
        auto framePosition = sf::Vector2i(
            hd::multiply(pCurrentAnimation->getFrameIndex(), animationSheet_.frameSize)
        );
        auto frameSize = static_cast<sf::Vector2i>(animationSheet_.frameSize);

        return {framePosition, frameSize};
    }


    void add(std::unique_ptr<Animation> animation) {
        animation_id id = animation->getID();
        animations.emplace(id, std::move(animation));
        if (pCurrentAnimation == nullptr) {
            set(id);
        }
    }

    void set(const animation_id &id) {
        auto *pNewAnimation = animations[id].get();
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

    [[nodiscard]] Animation* getCurrentAnimation() const {
        return pCurrentAnimation;
    }

    void update(const float &dt) const {
        pCurrentAnimation->update(dt);
        target_.setTextureRect(getCurrentFrame());
    }
};
#endif //BONK_GAME_ANIMATION_ENGINE_HPP