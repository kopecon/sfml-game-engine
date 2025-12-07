//
// Created by Andrew on 07/12/2025.
//

#include "Walking.hpp"
#include "../Player.hpp"


Walking::Walking() : State("WALKING") {}

Walking::Walking(Player &player) : State(player, "WALKING") {}

void Walking::act() {
    pPlayer->physics.speed = pPlayer->physics.walkingSpeed;
    pPlayer->movement.walk();
}
