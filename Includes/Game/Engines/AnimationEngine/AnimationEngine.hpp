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


template<EnumSetConcept AnimationSet>
class AnimationEngine {
    sf::Sprite &target_;
    std::unordered_map<typename AnimationSet::ID, std::unique_ptr<Animation<AnimationSet>>> animations_;
    Animation<AnimationSet> *pCurrentAnimation_{nullptr};
    std::unique_ptr<AnimationSheet> animationSheet_{nullptr};

public:
#pragma region constructors
    explicit AnimationEngine(sf::Sprite &target) :
        target_(target)
        {}
#pragma endregion

    void add(std::unique_ptr<Animation<AnimationSet>> animation) {
        typename AnimationSet::ID id = animation->getID();

        animations_.emplace(id, std::move(animation));
        if (pCurrentAnimation_ == nullptr) {
            set(id);
        }
    }

    void set(const typename AnimationSet::ID &id) {
        auto *pNewAnimation = animations_[id].get();
        if (pCurrentAnimation_ == nullptr) {
            pCurrentAnimation_ = pNewAnimation;
        }
        else if (pCurrentAnimation_ != pNewAnimation) {
            // Load desired animation
            pCurrentAnimation_ = pNewAnimation;
            // Reset the animation
            pCurrentAnimation_->reset();
        }
    }

    void setAnimationSheet(std::unique_ptr<AnimationSheet> animationSheet) {
        // target_.setTexture(animationSheet->texture);
        animationSheet_ = std::move(animationSheet);
    }

    [[nodiscard]] Animation<AnimationSet>* getCurrentAnimation() const {
        return pCurrentAnimation_;
    }

    [[nodiscard]] sf::IntRect getCurrentFrame() const {
        auto framePosition = sf::Vector2i(hd::multiply(
                pCurrentAnimation_->getFrame(),
                animationSheet_->frameSize)
                );

        auto frameSize = static_cast<sf::Vector2i>(animationSheet_->frameSize);

        return {framePosition, frameSize};
    }

    void update(const float &dt) const {
        if (animationSheet_) {
            pCurrentAnimation_->update(dt);
            target_.setTextureRect(getCurrentFrame());
        }
    }
};
#endif //BONK_GAME_ANIMATION_ENGINE_HPP