//
// Created by Andrew on 20/01/2026.
//

#ifndef BONK_GAME_ANIMATED_COMPOSITE_HPP
#define BONK_GAME_ANIMATED_COMPOSITE_HPP
#include "Composite.hpp"
#include "../../../Game/Engines/AnimationEngine/AnimationEngine.hpp"


template<EnumSetConcept AnimationSet>
class AnimatedComposite final: public Composite, public AnimationEngine<AnimationSet> {
public:
    explicit AnimatedComposite(std::unique_ptr<AnimationSheet> animationSheet) :
    Composite("animated", std::make_unique<sf::Sprite>(animationSheet->texture)),
    AnimationEngine<AnimationSet>(*sprite_, std::move(animationSheet)) {
    }
};


#endif //BONK_GAME_ANIMATED_COMPOSITE_HPP