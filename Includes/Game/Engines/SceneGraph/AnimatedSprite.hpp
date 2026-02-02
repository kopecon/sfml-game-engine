//
// Created by Andrew on 20/01/2026.
//

#ifndef BONK_GAME_ANIMATED_SPRITE_HPP
#define BONK_GAME_ANIMATED_SPRITE_HPP
#include "Composite.hpp"
#include "Sprite.hpp"
#include "../../../Game/Engines/AnimationEngine/AnimationEngine.hpp"
#include "../AnimationEngine/Animatable.hpp"


template<EnumSetConcept AnimationSet>
class AnimatedSprite : public Sprite, public Animatable {
protected:
    virtual void update() {}

public:
    explicit AnimatedSprite(std::unique_ptr<AnimationSheet> animationSheet) :
    Sprite(animationSheet->texture),
    animator(*sprite_, std::move(animationSheet)) {
        rename("animated sprite");
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


#endif //BONK_GAME_ANIMATED_SPRITE_HPP