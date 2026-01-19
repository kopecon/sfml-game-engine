//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/AnimationManager.hpp"
#include "../../../Includes/Entity/Player/Player.hpp"
#include "../../../Includes/Entity/Player/States/StateSet.hpp"
#include "../../../Includes/Game/Game.hpp"
#include "../../../Includes/Game/Engines/AnimationEngine/Animation.hpp"
#include "../../../Includes/World/World.hpp"
#include <cmath>


player::AnimationManager::AnimationManager(Player &player) :
    player_(player),
    engine_(player.getSprite(), AnimationSheet(player.getSprite().getTexture(), sf::Vector2u(32, 32))) {
    using enum StateSet::ID;
    engine_.add(std::make_unique<Animation<StateSet>>(IDLE,         2, true ));
    engine_.add(std::make_unique<Animation<StateSet>>(WINKING,      2, true ));
    engine_.add(std::make_unique<Animation<StateSet>>(WALKING,      4, true ));
    engine_.add(std::make_unique<Animation<StateSet>>(RUNNING,      8, true ));
    engine_.add(std::make_unique<Animation<StateSet>>(CROUCHING,    6, true ));
    engine_.add(std::make_unique<Animation<StateSet>>(JUMPING,      8, false));
    engine_.add(std::make_unique<Animation<StateSet>>(DYING,        8, false));
    engine_.add(std::make_unique<Animation<StateSet>>(DISAPPEARING, 4, false));
    engine_.add(std::make_unique<Animation<StateSet>>(ATTACKING,    8, false));
}

void player::AnimationManager::selectAnimation_() {
    using enum StateSet::ID;
    switch (player_.getState().ID) {
        case IDLE:
            engine_.set(IDLE);
            break;
        case WINKING:
            engine_.set(WINKING);
            break;
        case WALKING:
            engine_.set(WALKING);
            break;
        case RUNNING:
            engine_.set(RUNNING);
            break;
        case CROUCHING:
            engine_.set(CROUCHING);
            break;
        case JUMPING:
            engine_.set(JUMPING);
            break;
        case DISAPPEARING:
            engine_.set(DISAPPEARING);
            break;
        case DYING:
            engine_.set(DYING);
            break;
        case ATTACKING:
            engine_.set(ATTACKING);
            break;
        default:
            engine_.set(IDLE);
    }
}

void player::AnimationManager::updateFPS_() const {
    using enum StateSet::ID;
    auto &currentAnim = *engine_.pCurrentAnimation;
    switch (currentAnim.getID()) {
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
            const float speedFactor = std::fabs(
            player_.movement.getSpeed().x / player_.velocity.x
            );
            currentAnim.setSPF(1.f/currentAnim.getFPR() * speedFactor);
            break;
        }
        case RUNNING:{
            const float speedFactor = std::fabs(
            player_.movement.getSpeed().x / player_.velocity.x
            );
            currentAnim.setSPF(1.f/currentAnim.getFPR() * speedFactor * 0.7f);
            break;
        }
        case CROUCHING:{
            break;
        }
        case JUMPING:{
            const float speedFactor = std::fabs(
            player_.movement.getSpeed().y / player_.velocity.y
            );
            currentAnim.setSPF(1.f/currentAnim.getFPR() * speedFactor * 0.5f);
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
    selectAnimation_();
    updateFPS_();
    engine_.update(player_.game.time.get());
}
