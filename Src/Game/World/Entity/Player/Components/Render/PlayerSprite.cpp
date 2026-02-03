//
// Created by Andrew on 21/01/2026.
//

#include "Game/World/Entity/Player/Components/Render/PlayerSprite.hpp"
#include "Game/World/Entity/Player/Player.hpp"


namespace player {
    PlayerSprite::PlayerSprite(Player &player, std::unique_ptr<AnimationSheet> animationSheet):
        AnimatedSprite(std::move(animationSheet)),
        player_(player) {
        animator.addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::IDLE, 2, true));
        animator.addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::WINKING, 2, true));
        animator.addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::WALKING, 4, true));
        animator.addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::RUNNING, 8, true));
        animator.addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::CROUCHING, 6, true));
        animator.addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::JUMPING, 8, false));
        animator.addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::DYING, 8, false));
        animator.addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::DISAPPEARING, 4, false));
        animator.addAnimation(std::make_unique<Animation<StateSet>>(StateSet::ID::ATTACKING, 8, false));
    }

    void PlayerSprite::selectAnimation() {
        using enum StateSet::ID;

        auto pickWalkingOrRunning = [&] {
            // TODO: temporary magic number.
            if (std::abs(player_.velocity.x) - 100.f <= std::abs(player_.getMovement().getWalkingSpeed().x))
                animator.setAnimation(WALKING);
            else
                animator.setAnimation(RUNNING);;
        };

        switch (player_.getCurrentState().getID()) {
            case IDLE:
                if (!areClose(player_.velocity.x, 0.f)) {
                    pickWalkingOrRunning();
                }
                else animator.setAnimation(IDLE);
                break;
            case WINKING:
                animator.setAnimation(WINKING);
                break;
            case WALKING:
                pickWalkingOrRunning();
                break;
            case RUNNING:
                if (std::abs(player_.velocity.x) > std::abs(player_.getMovement().getWalkingSpeed().x))
                    animator.setAnimation(RUNNING);
                else animator.setAnimation(WALKING);
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
            case BRAKING:
                pickWalkingOrRunning();
                break;
            default:
                animator.setAnimation(IDLE);
        }
    }

    void PlayerSprite::updateFPS() const {
        using enum StateSet::ID;

        auto &currentAnimation = animator.getCurrentAnimation();

        switch (currentAnimation.getID()) {
            case WALKING : {
                const auto speedRatio = magnitudeRatio(player_.getMovement().getWalkingSpeed(), player_.velocity);
                currentAnimation.setSPF(1.f/static_cast<float>(currentAnimation.getFPR()) * speedRatio);
                break;
            }
            case RUNNING : {
                const auto speedRatio = magnitudeRatio(player_.getMovement().getRunningSpeed(), player_.velocity);
                currentAnimation.setSPF(1.f/static_cast<float>(currentAnimation.getFPR()) * speedRatio * 0.7f);
                break;
            }
            case JUMPING : {
                const auto speedRatio = magnitudeRatio(player_.getMovement().getSpeed(), player_.velocity);
                currentAnimation.setSPF(1.f/static_cast<float>(currentAnimation.getFPR()) * speedRatio * 0.6f);
                break;
            }
            case ATTACKING : {
                currentAnimation.setSPF(0.05f);
            }
            case CROUCHING : {
                currentAnimation.setSPF(0.05f);
            }
            default:
                break;
        }
    }

    void PlayerSprite::update() {
        selectAnimation();
        updateFPS();
    }
} // player