//
// Created by Andrew on 17/11/2025.
//

#include "../../../../Includes/Game/Engines/AnimationEngine/AnimationEngine.hpp"
#include "../../../../Includes/Game/Engines/AnimationEngine/AnimationSheet.hpp"
#include "../../../../Utils/utils.hpp"
#include "../../../../Includes/Game/Engines/Render/Composite.hpp"



AnimationEngine::AnimationEngine(sf::Sprite &target, std::unique_ptr<AnimationSheet> animationSheet):
    pTarget_(&target),
    animationSheet_(std::move(animationSheet))
    {}

AnimationEngine::AnimationEngine(const Composite &composite) :
    pTarget_(composite.getSprite())  //can be null
    {}

AnimationEngine::AnimationEngine(const Composite &composite, std::unique_ptr<AnimationSheet> animationSheet) :
    pTarget_(composite.getSprite()),  //can be null
    animationSheet_(std::move(animationSheet))
    {}

sf::IntRect AnimationEngine::getCurrentFrame() const {
    auto framePosition = sf::Vector2i(
        hd::multiply(pCurrentAnimation_->getFrameIndex(), animationSheet_->frameSize)
    );
    auto frameSize = static_cast<sf::Vector2i>(animationSheet_->frameSize);

    return {framePosition, frameSize};
}

void AnimationEngine::add(std::unique_ptr<Animation> animation) {
    animation_id id = animation->getID();
    animations_.emplace(id, std::move(animation));
    if (pCurrentAnimation_ == nullptr) {
        set(id);
    }
}

void AnimationEngine::set(const animation_id &id) {
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

Animation * AnimationEngine::getCurrentAnimation() const {
    return pCurrentAnimation_;
}

void AnimationEngine::update(const float &dt) const {
    if (pTarget_ && animationSheet_) {
        pCurrentAnimation_->update(dt);
        pTarget_->setTextureRect(getCurrentFrame());
    }
}
