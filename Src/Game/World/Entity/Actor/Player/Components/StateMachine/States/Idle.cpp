#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Idle.hpp"
#include "Game/World/Entity/Actor/Player/Player.hpp"


player::Idle::Idle(Player &player) : DefaultState(player, IDLE) {
    using namespace eval;
    // EDGES
    makeEdge(run_        , RUNNING);
    makeEdge(walk_       , WALKING);
    makeEdge(jump_       , JUMPING);
    makeEdge(wink_       , WINKING);
    makeEdge(attack_     , ATTACKING);
    makeEdge(concentrate_, CONCENTRATING);
    // ACTIONS
    addAction(MAIN_ACTION(dryEyes));
}

void player::Idle::dryEyes() {
    this->player().setEyeDryness(this->player().getEyeDryness() + 0.1f);
}
