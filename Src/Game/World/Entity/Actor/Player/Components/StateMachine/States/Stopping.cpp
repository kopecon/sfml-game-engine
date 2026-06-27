#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Stopping.hpp"
#include "Game/World/Entity/Actor/Player/Player.hpp"


player::Stopping::Stopping(Player &player)
    : DefaultState(player, DefaultStateSet::ID::STOPPING) {
    // EDGES
    makeEdge(jump_  , JUMPING  );
    makeEdge(eval::SlotsNotHeld({{left_}, {right_}}), WALKING  );
    makeEdge(attack_, ATTACKING);
    makeEdge(brake_ , BRAKING  );
    // ACTIONS
    addAction(MAIN_ACTION(stop));
}

void player::Stopping::setStateAnimation() {
    player().getRenderManager().getMainSprite().getAnimator().setAnimation(IDLE);
}

void player::Stopping::stop() {
    if (this->player().physics().isGrounded()) {
        this->player().getMovement().move({0.f, 0.f});
    }
}
