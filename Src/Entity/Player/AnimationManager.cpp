//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/AnimationManager.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/States/States.hpp"
#include "../../../Includes/World/World.hpp"
#include <cmath>


player::AnimationManager::AnimationManager() = default;

player::AnimationManager::AnimationManager(Player &player): pPlayer(&player) {}

void player::AnimationManager::selectAnimation() const {
    using enum States;

    switch (pPlayer->getStateID()) {
        case JUMPING : {
            pPlayer->animationManager.engine.set(JUMPING);
            pPlayer->animationManager.engine.animationSet[JUMPING].fps =
                    std::fabs(pPlayer->movement.walkingSpeed.y / pPlayer->movement.speed.y) * 24.f;
            break;
        }
        case WALKING : {
            pPlayer->animationManager.engine.set(WALKING);
            pPlayer->animationManager.engine.pCurrentAnimation->fps =
                    std::fabs(pPlayer->physics.velocity.x / pPlayer->movement.walkingSpeed.x) * static_cast<float>(
                        pPlayer->animationManager.engine.pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        case RUNNING : {
            pPlayer->animationManager.engine.set((RUNNING));
            pPlayer->animationManager.engine.pCurrentAnimation->fps = std::fabs(pPlayer->physics.velocity.x / pPlayer->movement.runningSpeed.x) * static_cast<float>(pPlayer->animationManager.engine.pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        case ATTACKING : {
            pPlayer->animationManager.engine.set((ATTACKING));
            pPlayer->animationManager.engine.pCurrentAnimation->fps = static_cast<float>(pPlayer->animationManager.engine.pCurrentAnimation->framesPerRow) * 3.f;
            break;
        }
        case DYING : {
            pPlayer->animationManager.engine.set((DYING));
            // animationManager.pCurrentAnimation->fps = static_cast<float>(animationManager.pCurrentAnimation->framesPerRow) * 3.f;
            break;
        }
        default: {
            pPlayer->animationManager.engine.set((IDLE));
        }
    }
}

void player::AnimationManager::update() const {
    selectAnimation();
    engine.update(pPlayer->pWorld->pGame->time.dt);
}
