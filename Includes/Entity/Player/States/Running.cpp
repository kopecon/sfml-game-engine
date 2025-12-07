//
// Created by Andrew on 07/12/2025.
//

#include "Running.hpp"
#include "../Player.hpp"


Running::Running(): State("RUNNING") {}

Running::Running(Player &player): State(player, "RUNNING") {}

void Running::act() {
    pPlayer->physics.speed = pPlayer->physics.runningSpeed;
    pPlayer->movement.walk();
}
