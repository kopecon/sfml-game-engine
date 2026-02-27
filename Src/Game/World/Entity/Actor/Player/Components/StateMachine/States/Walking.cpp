#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Walking.hpp"


player::Walking::Walking(Player &player)
    : DefaultState(player, DefaultStateSet::ID::WALKING) {
    // EDGES
    makeEdge(brake_, BRAKING);
    makeEdge(jump_, JUMPING);
    makeEdge(run_, RUNNING);
    makeEdge(attack_, ATTACKING);
    // ACTIONS
    addAction(MAIN_ACTION(walk));
}

void player::Walking::walk() {
    std::cout << player().stats().size.x <<"\n";
    if (this->player().physics().isGrounded()) {
        owner_.movement().move(speed_);
    }
    if (player().physics().isStill()) {
        animator().setAnimation(IDLE);
    } else {
        animator().setAnimation(WALKING);
    }
}

void player::Walking::adjustAnimationFPS() {
    const auto speedRatio = magnitudeRatio(speed_, player().physics().properties().velocity);
    auto &currentAnimation = animator().getCurrentAnimation();
    currentAnimation.setSPF(1.f / static_cast<float>(currentAnimation.getFPR()) * speedRatio);
}
