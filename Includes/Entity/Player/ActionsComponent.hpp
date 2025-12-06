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
    ActionsComponent();

    explicit ActionsComponent(Player &player);

    Player *pPlayer{nullptr};

    MovementComponent movement{};
    CombatComponent combat{};
};


#endif //BONK_GAME_ACTIONS_COMPONENT_HPP