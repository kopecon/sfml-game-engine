#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Running.hpp"


player::Running::Running(Player &player)
    : DefaultState(player, DefaultStateSet::ID::RUNNING),
      movement_(player.getMovement()) {
    // EDGES
    makeEdge(eval::SlotsNotHeld({{boost_}}), WALKING);
    makeEdge(brake_, BRAKING);
    makeEdge(attack_, ATTACKING);
    makeEdge(jump_, JUMPING);
    // ACTIONS
    addAction(MAIN_ACTION(run));
}

void player::Running::onEnter(const Context context) {
    DefaultState::onEnter(context);
    movement_.setSpeed(movement_.getRunningSpeed());
}

void player::Running::run() {
    if (this->player().physics().isGrounded()) {
        movement_.move(movement_.getSpeed());
    }
    if (player().physics().isStill()) {
        animator().setAnimation(IDLE);
    } else {
        animator().setAnimation(RUNNING);
    }
}

void player::Running::adjustAnimationFPS() {
    const auto speedRatio = magnitudeRatio(
        player().getMovement().getRunningSpeed(),
        player().physics().properties().velocity
    );
    auto &currentAnimation = animator().getCurrentAnimation();
    currentAnimation.setSPF(1.f / static_cast<float>(currentAnimation.getFPR()) * speedRatio * 0.7f);
}
