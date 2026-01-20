//
// Created by Andrew on 20/01/2026.
//

#ifndef BONK_GAME_ANIMATED_COMPOSITE_HPP
#define BONK_GAME_ANIMATED_COMPOSITE_HPP
#include "Composite.hpp"
#include "../AnimationEngine/Animatable.hpp"


template<EnumSetConcept AnimationSet>
class AnimatedComposite final: public Composite, public Animatable {
    std::unique_ptr<AnimationEngine<AnimationSet>> animator_{nullptr};
public:
    explicit AnimatedComposite(std::unique_ptr<AnimationSheet> animationSheet) {
        sprite_ = std::make_unique<sf::Sprite>(animationSheet->texture);
        sprite_->setTextureRect(sf::IntRect({0, 0}, static_cast<sf::Vector2i>(animationSheet->frameSize)));
        animator_ = std::make_unique<AnimationEngine<AnimationSet>>(*sprite_.get());
        animator_->setAnimationSheet(std::move(animationSheet));
    }

    std::any animator() override {
        return std::ref(*animator_.get());
    }
};


#endif //BONK_GAME_ANIMATED_COMPOSITE_HPP