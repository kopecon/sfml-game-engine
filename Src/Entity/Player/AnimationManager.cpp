//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/AnimationManager.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/States/StateSet.hpp"
#include "../../../Includes/World/World.hpp"
#include <cmath>


player::AnimationManager::AnimationManager() = default;

player::AnimationManager::AnimationManager(Player &player): pPlayer(&player) {}

void player::AnimationManager::selectAnimation() {
    using enum StateSet::ID;

    switch (pPlayer->getStateID()) {
        case JUMPING : {
            engine.set(JUMPING);
            engine.animationSet[JUMPING].fps =
                    std::fabs(pPlayer->movement.walkingSpeed.y / pPlayer->movement.speed.y) * 24.f;
            break;
        }
        case WALKING : {
            engine.set(WALKING);
            engine.pCurrentAnimation->fps =
                    std::fabs(pPlayer->physics.velocity.x / pPlayer->movement.walkingSpeed.x) * static_cast<float>(
                        engine.pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        case RUNNING : {
            engine.set((RUNNING));
            engine.pCurrentAnimation->fps = std::fabs(pPlayer->physics.velocity.x / pPlayer->movement.runningSpeed.x) * static_cast<float>(engine.pCurrentAnimation->framesPerRow) * 2.f;
            break;
        }
        case ATTACKING : {
            engine.set((ATTACKING));
            engine.pCurrentAnimation->fps = static_cast<float>(engine.pCurrentAnimation->framesPerRow) * 3.f;
            break;
        }
        case DYING : {
            engine.set((DYING));
            // animationManager.pCurrentAnimation->fps = static_cast<float>(animationManager.pCurrentAnimation->framesPerRow) * 3.f;
            break;
        }
        case NONE:
            break;
        case IDLE:
            engine.set((IDLE));
            break;
        case WINKING:
            engine.set((WINKING));
            break;
        case CROUCHING:
            engine.set((CROUCHING));
            break;
        case DISAPPEARING:
            engine.set((DISAPPEARING));
            break;
        case BRAKING:
            engine.set((IDLE));
            break;
        case STOPPING:
            engine.set((IDLE));
            break;
    }
}

void player::AnimationManager::update() {
    selectAnimation();
    engine.update(pPlayer->pWorld->pGame->time.dt);
}
