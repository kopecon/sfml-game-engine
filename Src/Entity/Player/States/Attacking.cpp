//
// Created by Andrew on 27/12/2025.
//

#include "../../../../Includes/Entity/Player/States/Attacking.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"

player::Attacking::Attacking(Player &player): PlayerState(player, StateSet::ID::ATTACKING) {
    // CONDITIONS
    Condition finished = [this]{return input_.key(controls_.attack).released;};
    const Action makeEdgeToPrevious = [this, finished] {
        // TODO: TEMPORARY ... this will create redundant edges.
        makeEdge(finished, player_.getPreviousState().getID());
    };
    addEnterAction(makeEdgeToPrevious);
    // ACTIONS
    addMainAction([&player]{player.getMovement().brake();});
}
