#pragma once

#include <SFML/Graphics.hpp>

#include "Video/Animation/Animation.hpp"
#include "Video/Animation/AnimationSheet.hpp"
#include "logger.hpp"
#include "math.hpp"
#include "utils.hpp"


template<EnumSetConcept AnimationSet>
class AnimationEngine;

template<EnumSetConcept AnimationSet>
struct AnimationSwapper {
    AnimationSwapper(AnimationEngine<AnimationSet> &engine, typename AnimationSet::ID id);

    ~AnimationSwapper();

private:
    AnimationEngine<AnimationSet> &engine_;
    typename AnimationSet::ID stash_{0};
};


template<EnumSetConcept AnimationSet>
AnimationSwapper<AnimationSet>::AnimationSwapper(AnimationEngine<AnimationSet> &engine, typename AnimationSet::ID id)
    : engine_(engine) {
    const auto next = engine.getAnimation(id);

    if (const auto &current = engine.pCurrentAnimation_) {
        if (current->status() == AnimationStatus::PLAYING) {
            if (next.priority() < current->priority()) {
                return;
            }
        }
        stash_ = current->id();
    }

    engine.setAnimation(id);
}

template<EnumSetConcept AnimationSet>
AnimationSwapper<AnimationSet>::~AnimationSwapper() {
    if (static_cast<bool>(stash_)) {
        engine_.setAnimation(stash_);
    }
}


template<EnumSetConcept AnimationSet>
class AnimationEngine final {
    friend AnimationSwapper<AnimationSet>;

public:
    using AnimID = typename AnimationSet::ID;

#pragma region constructors
    explicit AnimationEngine(sf::Sprite &target, const AnimationSheet<AnimationSet> &animationSheet);
#pragma endregion

    [[nodiscard]] Token<AnimationSwapper<AnimationSet> > swapAnimation(AnimID id) noexcept;

    [[nodiscard]] Animation<AnimationSet> &currentAnimation() const noexcept;

    [[nodiscard]] Animation<AnimationSet> &getAnimation(AnimID id) noexcept;

    void animate(float dt) const noexcept;

    void pause(AnimID id) noexcept;

private:
    sf::Sprite &target_;
    const AnimationSheet<AnimationSet> &animationSheet_;
    bool paused_{false};

    Animation<AnimationSet> *pCurrentAnimation_{nullptr}; // Can be null

    void setAnimation(const AnimID &id) noexcept;
};


template<EnumSetConcept AnimationSet>
AnimationEngine<AnimationSet>::AnimationEngine(sf::Sprite &target, const AnimationSheet<AnimationSet> &animationSheet)
    : target_(target),
      animationSheet_(animationSheet) {
}

template<EnumSetConcept AnimationSet>
Token<AnimationSwapper<AnimationSet> > AnimationEngine<AnimationSet>::swapAnimation(AnimID id) noexcept {
    return Token<AnimationSwapper<AnimationSet> >(*this, id);
}

template<EnumSetConcept AnimationSet>
Animation<AnimationSet> &AnimationEngine<AnimationSet>::currentAnimation() const noexcept {
    assert(pCurrentAnimation_);
    return *pCurrentAnimation_;
}

template<EnumSetConcept AnimationSet>
Animation<AnimationSet> &AnimationEngine<AnimationSet>::getAnimation(const AnimID id) noexcept {
    assert(animationSheet_.animations_.contains(id) && "Requested animation does not exist.");
    return *animationSheet_.animations_.at(id);
}

template<EnumSetConcept AnimationSet>
void AnimationEngine<AnimationSet>::animate(float dt) const noexcept {
    if (paused_) return;
    if (!pCurrentAnimation_) return;
    auto &anim = *pCurrentAnimation_;
    anim.play(dt);
    target_.setTextureRect(anim.currentFrame().rect);
}

template<EnumSetConcept AnimationSet>
void AnimationEngine<AnimationSet>::pause(AnimID id) noexcept {
    animationSheet_.animations_.at(id)->pause();
}

template<EnumSetConcept AnimationSet>
void AnimationEngine<AnimationSet>::setAnimation(const AnimID &id) noexcept {
    if (!animationSheet_.animations_.contains(id)) {
        LOG_WARN_ONCE("Animation: " + static_cast<std::string>(AnimationSet::name(id)) + " not found!", true);
        return;
    }

    auto &newAnimation = *animationSheet_.animations_.at(id).get();

    auto &current = pCurrentAnimation_;

    if (current) {
        if (*current == newAnimation) {
            return;
        }
    }

    newAnimation.reset();
    pCurrentAnimation_ = &newAnimation;
}
