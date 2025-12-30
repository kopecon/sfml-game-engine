//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/AnimationManager.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/States/StateSet.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/World/World.hpp"
#include <cmath>


player::AnimationManager::AnimationManager(Player &player) :
    player(player),
    engine({player.pTexture, {32, 32}}, player.shape) {
    using enum StateSet::ID;
    engine.add(AnimationEntry(IDLE,         2, true));
    engine.add(AnimationEntry(WINKING,      2, true));
    engine.add(AnimationEntry(WALKING,      4, true));
    engine.add(AnimationEntry(RUNNING,      8, true));
    engine.add(AnimationEntry(CROUCHING,    6, true));
    engine.add(AnimationEntry(JUMPING,      8, false));
    engine.add(AnimationEntry(DYING,        8, false));
    engine.add(AnimationEntry(DISAPPEARING, 4, false));
    engine.add(AnimationEntry(ATTACKING,    8, false));
}

void player::AnimationManager::selectAnimation() {
    using enum StateSet::ID;

    switch (player.getState()->ID) {
        case IDLE:
            engine.set(IDLE);
            break;
        case WINKING:
            engine.set(WINKING);
            break;
        case WALKING:
            engine.set(WALKING);
            break;
        case RUNNING:
            engine.set(RUNNING);
            break;
        case CROUCHING:
            engine.set(CROUCHING);
            break;
        case JUMPING:
            engine.set(JUMPING);
            break;
        case DISAPPEARING:
            engine.set(DISAPPEARING);
            break;
        case DYING:
            engine.set(DYING);
            break;
        case ATTACKING:
            engine.set(ATTACKING);
            break;
        default:
            engine.set(IDLE);
    }
}

void player::AnimationManager::updateFPS() const {
    using enum StateSet::ID;
    const auto currentAnim = engine.pCurrentAnimation;
    switch (currentAnim->ID) {
        case NONE: {
            break;
        }
        case IDLE: {
            break;
        }
        case WINKING: {
            break;
        }

        case WALKING:{
            const float seedFactor = std::fabs(
            player.movement.getSpeed().x / player.velocity.x
            );
            currentAnim->spf = 1.f/currentAnim->fps * seedFactor;
            break;
        }
        case RUNNING:{
            const float seedFactor = std::fabs(
            player.movement.getSpeed().x / player.velocity.x
            );
            currentAnim->spf = 1.f/currentAnim->fps * seedFactor * 0.7f;
            break;
        }
        case CROUCHING:{
            break;
        }
        case JUMPING:{
            const float seedFactor = std::fabs(
            player.movement.getSpeed().y / player.velocity.y
            );
            currentAnim->spf = 1.f/currentAnim->fps * seedFactor * 0.5f;
            break;
        }
        case DISAPPEARING:{
            break;
        }
        case DYING:{
            break;
        }
        case ATTACKING:{
            break;
        }
        case BRAKING:{
            break;
        }
        case STOPPING:{
            break;
        }
    }

}

void player::AnimationManager::update() {
    selectAnimation();
    updateFPS();
    engine.update(player.game.time.dt);
}
