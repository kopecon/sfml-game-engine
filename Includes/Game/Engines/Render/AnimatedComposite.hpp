//
// Created by Andrew on 20/01/2026.
//

#ifndef BONK_GAME_ANIMATED_COMPOSITE_HPP
#define BONK_GAME_ANIMATED_COMPOSITE_HPP
#include "Composite.hpp"
#include "../../../Game/Engines/AnimationEngine/AnimationEngine.hpp"
#include "../AnimationEngine/Animatable.hpp"


template<EnumSetConcept AnimationSet>
class AnimatedComposite : public Composite, public Animatable {
protected:
    virtual void update() {}

public:
    explicit AnimatedComposite(std::unique_ptr<AnimationSheet> animationSheet) :
    Composite("animated", std::make_unique<sf::Sprite>(animationSheet->texture)),
    animator(*sprite_, std::move(animationSheet)) {
    }

    AnimationEngine<AnimationSet> animator;

    Animatable* asAnimatable() override {
        return this;
    }

    void animate(float dt) override {
        update();
        animator.animate(dt);
    }
};


#endif //BONK_GAME_ANIMATED_COMPOSITE_HPP