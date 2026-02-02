//
// Created by Andrew on 17/11/2025.
//

#ifndef BONK_GAME_ANIMATION_ENGINE_HPP
#define BONK_GAME_ANIMATION_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "Game/Engines/AnimationEngine/Animation.hpp"
#include "Game/Engines/AnimationEngine/AnimationSheet.hpp"
#include "Utils/utils.hpp"


template<EnumSetConcept AnimationSet>
class AnimationEngine final {
    sf::Sprite &target_;
    std::unique_ptr<AnimationSheet> animationSheet_{nullptr};  // Can't be null
    std::unordered_map<typename AnimationSet::ID, std::unique_ptr<Animation<AnimationSet>>> animations_;
    Animation<AnimationSet> *pCurrentAnimation_{nullptr};  // Can be null
    std::function<void()> selectAnimationStrategy_{};

public:
#pragma region constructors
    explicit AnimationEngine(sf::Sprite &target, std::unique_ptr<AnimationSheet> animationSheet) :
        target_(target),
        animationSheet_(std::move(animationSheet))
        {target.setTextureRect(sf::IntRect({0, 0}, static_cast<sf::Vector2i>(animationSheet_->frameSize)));}
#pragma endregion

    void addAnimation(std::unique_ptr<Animation<AnimationSet>> animation) {
        typename AnimationSet::ID id = animation->getID();

        animations_.emplace(id, std::move(animation));

        if (pCurrentAnimation_ == nullptr) {
            pCurrentAnimation_ = animations_[id].get();
        }
    }

    void setAnimation(const typename AnimationSet::ID &id) {
        if (!animations_.contains(id)) return;

        auto *pNewAnimation = animations_[id].get();

        if (pCurrentAnimation_ != pNewAnimation) {
            // Load desired animation
            pCurrentAnimation_ = pNewAnimation;
            // Reset the animation
            pCurrentAnimation_->reset();
        }
    }

    void setSelectionStrategy(std::function<void()> strategy) {
        selectAnimationStrategy_ = std::move(strategy);
    }

    void changeAnimationSheet(std::unique_ptr<AnimationSheet> animationSheet) {
        target_.setTexture(animationSheet->texture);
        animationSheet_ = std::move(animationSheet);
    }

    [[nodiscard]] Animation<AnimationSet>& getCurrentAnimation() const {
        assert(pCurrentAnimation_);
        return *pCurrentAnimation_;
    }

    [[nodiscard]] sf::IntRect getCurrentFrame() const {
        sf::Vector2i framePosition{0, 0};
        if (pCurrentAnimation_) {
             framePosition = sf::Vector2i(hd::multiply(
                pCurrentAnimation_->getFrame(),
                animationSheet_->frameSize)
                );
        }

        auto frameSize = static_cast<sf::Vector2i>(animationSheet_->frameSize);

        return {framePosition, frameSize};
    }

    void animate(float dt) const {
        if (!pCurrentAnimation_ || !animationSheet_) return;

        if (selectAnimationStrategy_) selectAnimationStrategy_();

        pCurrentAnimation_->play(dt);
        target_.setTextureRect(getCurrentFrame());
    }
};
#endif //BONK_GAME_ANIMATION_ENGINE_HPP