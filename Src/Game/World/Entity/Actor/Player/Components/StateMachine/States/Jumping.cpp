#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Jumping.hpp"
#include "Game/World/World.hpp"


player::Jumping::Jumping(Player &player) : DefaultState(player, DefaultStateSet::ID::JUMPING) {
    // HELPER CONDITION
    Condition grounded = [this] { return this->player().physics().isGrounded(); };
    // CONDITIONS
    const auto running = eval::Conditioned(
        [grounded, this] { return grounded() && context_.from.id() == RUNNING; }
    );
    const auto walking = eval::Conditioned(
        [grounded, this] { return grounded() && context_.from.id() == WALKING; }
    );
    const auto landed = eval::Conditioned([grounded] { return grounded(); });
    // EDGES
    makeEdge(attack_, ATTACKING);
    makeEdge(running, RUNNING);
    makeEdge(walking, WALKING);
    makeEdge(landed, IDLE);
    makeEdge(landed, BRAKING);
    // ACTIONS
    addAction(ENTER_ACTION(jump));
}

void player::Jumping::jump() {
    if (this->player().physics().isGrounded()) {
        constexpr float magicConst = 2500.f; // Magic number is tweaked experimentally
        this->player().physics().properties().velocity.y =
                -this->player().world.gravity * this->player().getMovement().getSpeed().y / magicConst;
    }
}

void player::Jumping::adjustAnimationFPS() {
    const auto speedRatio = magnitudeRatio(this->player().getMovement().getSpeed(),
                                           this->player().physics().properties().velocity);
    auto &currentAnimation = this->player().getRenderManager().getMainSprite().getAnimator().getCurrentAnimation();
    currentAnimation.setSPF(1.f / static_cast<float>(currentAnimation.getFPR()) * speedRatio * 0.6f);
}
