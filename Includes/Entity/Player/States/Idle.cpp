//
// Created by Andrew on 07/12/2025.
//

#include "Idle.hpp"

Idle::Idle(): State("IDLE") {}

Idle::Idle(Player &player): State(player, "IDLE") {}

void Idle::act() {}
