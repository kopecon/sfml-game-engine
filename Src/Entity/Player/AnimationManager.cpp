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

#include "../../../Includes/Game/Engines/AnimationEngine/Animatable.hpp"


player::AnimationManager::AnimationManager(Player &player) :
    player_(player),
    animator_(
        std::any_cast<std::reference_wrapper<AnimationEngine<StateSet>>>(
            dynamic_cast<Animatable*>(&player.render.getRoot())->animator())
        )
    {
    using enum StateSet::ID;
    animator_.add(std::make_unique<Animation<StateSet>>(IDLE,         2, true ));
    animator_.add(std::make_unique<Animation<StateSet>>(WINKING,      2, true ));
    animator_.add(std::make_unique<Animation<StateSet>>(WALKING,      4, true ));
    animator_.add(std::make_unique<Animation<StateSet>>(RUNNING,      8, true ));
    animator_.add(std::make_unique<Animation<StateSet>>(CROUCHING,    6, true ));
    animator_.add(std::make_unique<Animation<StateSet>>(JUMPING,      8, false));
    animator_.add(std::make_unique<Animation<StateSet>>(DYING,        8, false));
    animator_.add(std::make_unique<Animation<StateSet>>(DISAPPEARING, 4, false));
    animator_.add(std::make_unique<Animation<StateSet>>(ATTACKING,    8, false));
}

void player::AnimationManager::selectAnimation_() const {
    animator_.set(player_.getState().getID());
}

void player::AnimationManager::updateFPS_() const {
    using enum StateSet::ID;
    if (const auto pCurrentAnim = animator_.getCurrentAnimation()) {
        switch (pCurrentAnim->getID()) {
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

void player::AnimationManager::update() const {
    selectAnimation_();
    updateFPS_();
    animator_.update(player_.game.time.get());
}
