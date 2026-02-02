#include "Game/World/Entity/Player/Components/States/Idle.hpp"
#include "Game/World/Entity/Player/Player.hpp"


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
    addMainAction(mainAction());
}

Action player::Idle::mainAction() const {
    Player &player = player_;
    return [&player] {
        player.setEyeDryness(player.getEyeDryness() + 0.1f);
        player.getMovement().brake();
    };
}
