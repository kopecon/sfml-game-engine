//
// Created by Andrew on 06/12/2025.
//

#include "../../../Includes/Entity/Player/ActionsComponent.hpp"

ActionsComponent::ActionsComponent() = default;

ActionsComponent::ActionsComponent(Player &player): pPlayer(&player), movement(player), combat(player) {}
