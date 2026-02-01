#include "../../../../Includes/Entity/Player/States/Idle.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


using enum player::StateSet::ID;

player::Idle::Idle(Player &player) : PlayerState(player, IDLE) {
    // EDGES
    makeEdge(stop, STOPPING);
    makeEdge(run, RUNNING);
    makeEdge(walk, WALKING);
    makeEdge(jump, JUMPING);
    makeEdge(wink, WINKING);
    makeEdge(attack, ATTACKING);
    makeEdge(concentrate, CONCENTRATING);
    // ACTIONS
    addAction(mainAction());
}

Action player::Idle::mainAction() const {
    Player &player = player_;
    return [&player] {
        player.setEyeDryness(player.getEyeDryness() + 0.1f);
        player.getMovement().brake();
    };
}
