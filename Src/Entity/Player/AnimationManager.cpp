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
    animator_(player.render.root.animator)
{
    animator_.setAnimationSheet(std::make_unique<AnimationSheet>(
            player.render.root.getSprite()->getTexture(),
            sf::Vector2u(32, 32)
            ));
    animator_.setTarget(*player.render.root.getSprite());
    using enum StateSet::ID;
    addAnimation<StateSet>(IDLE,         2, true );
    addAnimation<StateSet>(WINKING,      2, true );
    addAnimation<StateSet>(WALKING,      4, true );
    addAnimation<StateSet>(RUNNING,      8, true );
    addAnimation<StateSet>(CROUCHING,    6, true );
    addAnimation<StateSet>(JUMPING,      8, false);
    addAnimation<StateSet>(DYING,        8, false);
    addAnimation<StateSet>(DISAPPEARING, 4, false);
    addAnimation<StateSet>(ATTACKING,    8, false);
}

void player::AnimationManager::selectAnimation_() {
    using enum StateSet::ID;
    switch (player_.getState().getID()) {
        case IDLE:
            setAnimation<StateSet>(IDLE);
            break;
        case WINKING:
            setAnimation<StateSet>(WINKING);
            break;
        case WALKING:
            setAnimation<StateSet>(WALKING);
            break;
        case RUNNING:
            setAnimation<StateSet>(RUNNING);
            break;
        case CROUCHING:
            setAnimation<StateSet>(CROUCHING);
            break;
        case JUMPING:
            setAnimation<StateSet>(JUMPING);
            break;
        case DISAPPEARING:
            setAnimation<StateSet>(DISAPPEARING);
            break;
        case DYING:
            setAnimation<StateSet>(DYING);
            break;
        case ATTACKING:
            setAnimation<StateSet>(ATTACKING);
            break;
        default:
            setAnimation<StateSet>(IDLE);
    }
}

void player::AnimationManager::updateFPS_() const {
    using enum StateSet::ID;
    if (const auto pCurrentAnim = animator_.getCurrentAnimation()) {
        switch (static_cast<StateSet::ID>(pCurrentAnim->getID())) {
            case WALKING:{
                const float speedFactor = std::fabs(
                player_.movement.getSpeed().x / player_.velocity.x
                );
                pCurrentAnim->setSPF(1.f/static_cast<float>(pCurrentAnim->getFPR()) * speedFactor);
                break;
            }
            case RUNNING:{
                const float speedFactor = std::fabs(
                player_.movement.getSpeed().x / player_.velocity.x
                );
                pCurrentAnim->setSPF(1.f/static_cast<float>(pCurrentAnim->getFPR()) * speedFactor * 0.7f);
                break;
            }
            case JUMPING:{
                const float speedFactor = std::fabs(
                player_.movement.getSpeed().y / player_.velocity.y
                );
                pCurrentAnim->setSPF(1.f/static_cast<float>(pCurrentAnim->getFPR()) * speedFactor * 0.5f);
                break;
            }
            default:
                break;
        }
    }
}

void player::AnimationManager::update() {
    selectAnimation_();
    updateFPS_();
}
