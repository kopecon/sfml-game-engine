//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/AnimationManager.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/World/World.hpp"


player::AnimationManager::AnimationManager() = default;

player::AnimationManager::AnimationManager(Player &player): pPlayer(&player) {}

void player::AnimationManager::selectAnimation() const {
    using enum player::States;
    switch (pPlayer->stateManager.state) {
        case JUMPING : {
            pPlayer->animationManager.set(JUMPING);
            pPlayer->animationManager.animationSet[JUMPING].fps = std::fabs(pPlayer->movement.walkingSpeed.y / pPlayer->movement.speed.y)*24.f;
            break;
        }
        case WALKING : {
            pPlayer->animationManager.set(WALKING);
            pPlayer->animationManager.pCurrentAnimation->fps = std::fabs(pPlayer->physics.velocity.x / pPlayer->movement.walkingSpeed.x) * static_cast<float>(pPlayer->animationManager.pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        case RUNNING : {
            pPlayer->animationManager.set(RUNNING);
            pPlayer->animationManager.pCurrentAnimation->fps = std::fabs(pPlayer->physics.velocity.x / pPlayer->movement.runningSpeed.x) * static_cast<float>(pPlayer->animationManager.pCurrentAnimation->framesPerRow) * 2.f;
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

void player::AnimationManager::update() const {
    selectAnimation();
    AnimationEngine::update(pPlayer->pWorld->pGame->time.dt);
}
