#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Braking.hpp"


player::Braking::Braking(Player& player) : DefaultState(player, BRAKING) {
    // EDGES
    makeEdge(walk_ , WALKING);
    makeEdge(run_  , RUNNING);
    makeEdge(idle_ , IDLE);
    // ACTIONS
    addAction(MAIN_ACTION(brake));
}

void player::Braking::brake() {
    if (auto &physics = this->player().physics(); physics.isGrounded()) {
        this->player().getMovement().move({0.f, 0.f});
        if (physics.properties().velocity.x <= 50.f) {
            physics.totalStop();
        }
    }
}
