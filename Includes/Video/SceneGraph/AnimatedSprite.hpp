#pragma once

#include "Video/Animation/Animatable.hpp"
#include "Video/Animation/AnimationSheet.hpp"
#include "Video/Animation/AnimationEngine.hpp"
#include "Video/SceneGraph/Sprite.hpp"
#include "EnumSet.hpp"


namespace render {
    template<EnumSetConcept AnimationSet>
    class AnimatedSprite : public Sprite, public AnimationSheet<AnimationSet>, public Animatable {
    public:
        explicit AnimatedSprite(const sf::Texture &texture)
            : Sprite(texture),
              AnimationSheet<AnimationSet>(texture),
              animator_(*sprite_, *this) {
        }

        // GETTERS
        Animatable *asAnimatable() noexcept override {
            return this;
        }

        AnimationEngine<AnimationSet> &getAnimator() noexcept {
            return animator_;
        }

        // UPDATE
        void animate(float dt) noexcept override {
            animator_.animate(dt);
        }

        void setTextureRect(const sf::IntRect &rect) noexcept override {
            sprite_->setTextureRect(rect);
        }

    protected:
        AnimationEngine<AnimationSet> animator_;
    };
} // render
