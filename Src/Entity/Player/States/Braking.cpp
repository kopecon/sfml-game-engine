//
// Created by Andrew on 01/02/2026.
//

#include "../../../../Includes/Entity/Player/States/Braking.hpp"


player::Braking::Braking(Player& player) : PlayerState(player, BRAKING) {
    // EDGES
    makeEdge(stop, STOPPING);
    makeEdge(walk, WALKING);
    makeEdge(run, RUNNING);
    makeEdge(idle, IDLE);
    // ACTIONS
    addMainAction([this]{player_.getMovement().brake();});
}
