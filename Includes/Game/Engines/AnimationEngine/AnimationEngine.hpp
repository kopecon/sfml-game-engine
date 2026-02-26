#ifndef BONK_GAME_ANIMATION_ENGINE_HPP
#define BONK_GAME_ANIMATION_ENGINE_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Game/Engines/AnimationEngine/Animation.hpp"
#include "Game/Engines/AnimationEngine/AnimationSheet.hpp"
#include "Utils/utils.hpp"
#include "Utils/logger.hpp"


template<EnumSetConcept AnimationSet>
class AnimationEngine final {
public:
#pragma region constructors
    explicit AnimationEngine(sf::Sprite &target, std::unique_ptr<AnimationSheet> animationSheet)
        : target_(target),
          animationSheet_(std::move(animationSheet)) {
        target.setTextureRect(sf::IntRect({0, 0}, static_cast<sf::Vector2i>(animationSheet_->frameSize)));
    }
#pragma endregion

    void addAnimation(std::unique_ptr<Animation<AnimationSet> > animation) {
        typename AnimationSet::ID id = animation->getID();

        animations_.emplace(id, std::move(animation));

        if (pCurrentAnimation_ == nullptr) {
            pCurrentAnimation_ = animations_.at(id).get();
        }
    }

    void setAnimation(const typename AnimationSet::ID &id) {
        if (!animations_.contains(id)) {
            LOG_WARN_ONCE("Animation: " + static_cast<std::string>(AnimationSet::name(id)) + " not found!", true);
            return;
        }

        auto *pNewAnimation = animations_.at(id).get();

        if (pCurrentAnimation_ != pNewAnimation) {
            // Load desired animation
            pCurrentAnimation_ = pNewAnimation;
            // Reset the animation
            pCurrentAnimation_->reset();
        }
    }

    void changeAnimationSheet(std::unique_ptr<AnimationSheet> animationSheet) {
        target_.setTexture(animationSheet->texture);
        animationSheet_ = std::move(animationSheet);
    }

    [[nodiscard]] Animation<AnimationSet> &getCurrentAnimation() const {
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
        pCurrentAnimation_->play(dt);
        target_.setTextureRect(getCurrentFrame());
    }

private:
    sf::Sprite &target_;
    std::unique_ptr<AnimationSheet> animationSheet_{nullptr}; // Can't be null
    std::unordered_map<typename AnimationSet::ID, std::unique_ptr<Animation<AnimationSet> > > animations_;
    Animation<AnimationSet> *pCurrentAnimation_{nullptr}; // Can be null
};
#endif //BONK_GAME_ANIMATION_ENGINE_HPP
