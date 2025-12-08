//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/AnimationManager.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"


AnimationManager::AnimationManager() = default;

AnimationManager::AnimationManager(Player &player): pPlayer(&player) {}

void AnimationManager::selectAnimation() const {
    using enum StateManager::States;
    switch (pPlayer->stateManager.state) {
        case JUMPING : {
            pPlayer->animationManager.set(JUMPING);
            pPlayer->animationManager.animationSet[JUMPING].fps = std::fabs(pPlayer->physics.walkingSpeed.y / pPlayer->physics.speed.y)*24.f;
            break;
        }
        case WALKING : {
            pPlayer->animationManager.set(WALKING);
            pPlayer->animationManager.pCurrentAnimation->fps = std::fabs(pPlayer->physics.velocity.x / pPlayer->physics.walkingSpeed.x) * static_cast<float>(pPlayer->animationManager.pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        case RUNNING : {
            pPlayer->animationManager.set(RUNNING);
            pPlayer->animationManager.pCurrentAnimation->fps = std::fabs(pPlayer->physics.velocity.x / pPlayer->physics.runningSpeed.x) * static_cast<float>(pPlayer->animationManager.pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        case ATTACKING : {
            pPlayer->animationManager.set(ATTACKING);
            pPlayer->animationManager.pCurrentAnimation->fps = static_cast<float>(pPlayer->animationManager.pCurrentAnimation->framesPerRow) * 3.f;
            break;
        }
        case DYING : {
            pPlayer->animationManager.set(DYING);
            // animationManager.pCurrentAnimation->fps = static_cast<float>(animationManager.pCurrentAnimation->framesPerRow) * 3.f;
            break;
        }
        default: {
            pPlayer->animationManager.set(IDLE);
        }
    }
}
