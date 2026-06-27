#ifndef BONK_GAME_ANIMATED_SPRITE_HPP
#define BONK_GAME_ANIMATED_SPRITE_HPP
#include "Composite.hpp"
#include "Sprite.hpp"
#include "Game/Engines/AnimationEngine/AnimationEngine.hpp"
#include "Game/Engines/AnimationEngine/Animatable.hpp"


template<EnumSetConcept AnimationSet>
class AnimatedSprite : public Sprite, public Animatable {
public:
    explicit AnimatedSprite(std::unique_ptr<AnimationSheet> animationSheet)
        : Sprite(animationSheet->texture),
          animator_(*sprite_, std::move(animationSheet)) {
        rename("animated sprite");
    }
    // GETTERS
    Animatable *asAnimatable() override {
        return this;
    }
    AnimationEngine<AnimationSet>& getAnimator() {
        return animator_;
    }
    // UPDATE
    void animate(float dt) override {
        animator_.animate(dt);
    }

protected:
    AnimationEngine<AnimationSet> animator_;
};


#endif //BONK_GAME_ANIMATED_SPRITE_HPP
