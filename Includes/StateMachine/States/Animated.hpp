#pragma once

#include "EntityManager/Entity/Entity.hpp"
#include "StateMachine/States/State.hpp"
#include "Video/Animation/AnimationEngine.hpp"
#include "Video/SceneGraph/AnimatedSprite.hpp"
#include "EnumSet.hpp"


namespace state_machine::state {
    template<IsState State, EnumSetConcept AnimationSet>
    class Animated : public State {
    public:
        template<IsEntity Owner, typename Sprite>
            requires (std::derived_from<Sprite, render::AnimatedSprite<AnimationSet> >)
        Animated(Owner &owner, TypeTag<Sprite>, typename AnimationSet::ID animID)
            : State(owner),
              sprite_(owner.render().get(type<Sprite>)),
              animID_(animID) {
            this->addEnterAction([this] { animationToken_ = sprite_.getAnimator().swapAnimation(animID_); });
            this->addMainAction([this] {
                if (sprite_.getAnimator().getAnimation(animID_).status() == AnimationStatus::FINISHED) {
                    this->quit();
                }
            });
            this->addExitAction([this] { animationToken_.consume(); });
        }

    private:
        render::AnimatedSprite<AnimationSet> &sprite_;
        AnimationSet::ID animID_{};
        Token<AnimationSwapper<AnimationSet> > animationToken_{};
    };
}
