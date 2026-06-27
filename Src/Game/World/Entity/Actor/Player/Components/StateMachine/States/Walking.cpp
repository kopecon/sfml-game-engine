#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Walking.hpp"


player::Walking::Walking(Player &player)
    : DefaultState(player, DefaultStateSet::ID::WALKING),
      movement_(player.getMovement()) {
    // EDGES
    makeEdge(brake_, BRAKING);
    makeEdge(jump_, JUMPING);
    makeEdge(run_, RUNNING);
    makeEdge(attack_, ATTACKING);
    // ACTIONS
    addAction(MAIN_ACTION(walk));
}

void player::Walking::onEnter(const Context context) {
    DefaultState::onEnter(context);
    movement_.setSpeed(movement_.getWalkingSpeed());
}

void player::Walking::walk() {
    if (this->player().physics().isGrounded()) {
        movement_.move(movement_.getSpeed());
    }
    if (player().physics().isStill()) {
        animator().setAnimation(IDLE);
    } else {
        animator().setAnimation(WALKING);
    }
}

void player::Walking::adjustAnimationFPS() {
    const auto speedRatio = magnitudeRatio(
        player().getMovement().getWalkingSpeed(),
        player().physics().properties().velocity
    );
    auto &currentAnimation = animator().getCurrentAnimation();
    currentAnimation.setSPF(1.f / static_cast<float>(currentAnimation.getFPR()) * speedRatio);
}
