//
// Created by Andrew on 21/01/2026.
//

#include "../../../Includes/Entity/Player/PlayerSprite.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"

namespace player {
    void PlayerSprite::selectAnimation() {
        using enum StateSet::ID;
        switch (player.getCurrentState().getID()) {
            case IDLE:
                animator.setAnimation(IDLE);
                break;
            case WINKING:
                animator.setAnimation(WINKING);
                break;
            case WALKING:
                animator.setAnimation(WALKING);
                break;
            case RUNNING:
                animator.setAnimation(RUNNING);
                break;
            case CROUCHING:
                animator.setAnimation(CROUCHING);
                break;
            case JUMPING:
                animator.setAnimation(JUMPING);
                break;
            case DISAPPEARING:
                animator.setAnimation(DISAPPEARING);
                break;
            case DYING:
                animator.setAnimation(DYING);
                break;
            case ATTACKING:
                animator.setAnimation(ATTACKING);
                break;
            default:
                animator.setAnimation(IDLE);
        }
    }

    void PlayerSprite::updateFPS() const {
        using enum StateSet::ID;

        auto &currentAnimation = animator.getCurrentAnimation();

        const auto speedRatio = hd::abs(hd::divide(player.velocity, player.getMovement().getSpeed()));

        switch (currentAnimation.getID()) {
            case WALKING : {
                currentAnimation.setSPF(1.f/static_cast<float>(currentAnimation.getFPR()) * speedRatio.x);
                break;
            }
            case RUNNING : {
                currentAnimation.setSPF(1.f/static_cast<float>(currentAnimation.getFPR()) * speedRatio.x * 0.7f);
                break;
            }
            case JUMPING : {
                currentAnimation.setSPF(1.f/static_cast<float>(currentAnimation.getFPR()) * speedRatio.y * 0.6f);
                break;
            }
            case ATTACKING : {
                currentAnimation.setSPF(0.05f);
                break;
            }
            default:
                break;
        }
    }

    void PlayerSprite::update() {
        selectAnimation();
        updateFPS();
    }

    PlayerSprite::PlayerSprite(Player &player, std::unique_ptr<AnimationSheet> animationSheet):
        AnimatedSprite(std::move(animationSheet)),
        player(player) {
        animator.addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::IDLE, 2, true));
        animator.addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::WINKING, 2, true));
        animator.addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::WALKING, 4, true));
        animator.addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::RUNNING, 8, true));
        animator.addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::CROUCHING, 6, true));
        animator.addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::JUMPING, 8, false));
        animator.addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::DYING, 8, false));
        animator.addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::DISAPPEARING, 4, false));
        animator.addAnimation(std::make_unique<Animation<StateSet> >(StateSet::ID::ATTACKING, 8, false));
    }
} // player