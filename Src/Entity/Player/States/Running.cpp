#include "../../../../Includes/Entity/Player/States/Running.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"

player::Running::Running(Player &player): PlayerState(player, StateSet::ID::RUNNING) {
    // EDGES
    makeEdge(stop, STOPPING);
    makeEdge(brake, BRAKING);
    makeEdge(attack, ATTACKING);
    makeEdge(jump, JUMPING);
    makeEdge([this]{return walk() && !run();}, WALKING);
    // ACTIONS
    const Action setDirection = [this] {
        if (input_.key(controls_.left).down) {
            player_.getMovement().setLeftWalkingDirection();
        }
        else {
            player_.getMovement().setRightWalkingDirection();
        }
    };
    addAction(setDirection);
    addAction([&player]{player.getMovement().walk();});
}
