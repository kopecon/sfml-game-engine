//
// Created by Andrew on 21/01/2026.
//

#include "../../../Includes/Entity/Player/PlayerSprite.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"

namespace player {
    PlayerSprite::PlayerSprite(Player &player, std::unique_ptr<AnimationSheet> animationSheet):
        AnimatedComposite(std::move(animationSheet)),
        player(player) {
        addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::IDLE, 2, true));
        addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::WINKING, 2, true));
        addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::WALKING, 4, true));
        addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::RUNNING, 8, true));
        addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::CROUCHING, 6, true));
        addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::JUMPING, 8, false));
        addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::DYING, 8, false));
        addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::DISAPPEARING, 4, false));
        addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::ATTACKING, 8, false));
    }

    void PlayerSprite::selectAnimation() {
        setAnimation(player.getState().getID());
    }
} // player