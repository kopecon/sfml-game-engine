//
// Created by Andrew on 06/12/2025.
//

#ifndef BONK_GAME_ACTIONS_COMPONENT_HPP
#define BONK_GAME_ACTIONS_COMPONENT_HPP
#include "CombatComponent.hpp"
#include "MovementComponent.hpp"


class Player;

class ActionsComponent {
public:
    enum class States {
        IDLE,
        WINKING,
        WALKING,
        RUNNING,
        CROUCHING,
        JUMPING,
        DISAPPEARING,
        DYING,
        ATTACKING,
        BRAKING,
        STOPPING,
    };
    ActionsComponent();

    explicit ActionsComponent(Player &player);

    Player *pPlayer{nullptr};
    States state{States::IDLE};
    MovementComponent movement{};
    CombatComponent combat{};

};


#endif //BONK_GAME_ACTIONS_COMPONENT_HPP