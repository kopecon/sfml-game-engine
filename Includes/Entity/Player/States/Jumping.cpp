//
// Created by Andrew on 07/12/2025.
//

#include "Jumping.hpp"
#include "../Player.hpp"


Jumping::Jumping(): State("JUMPING") {}

Jumping::Jumping(Player &player): State(player, "JUMPING") {}

void Jumping::act() {
    pPlayer->movement.jump();
}
