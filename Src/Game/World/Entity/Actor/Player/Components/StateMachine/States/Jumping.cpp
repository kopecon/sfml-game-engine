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
}

void player::Jumping::onEnter(const Context context) {
    DefaultState::onEnter(context);
    speed_.y = std::abs(player().physics().properties().velocity.x);
    speed_.y = std::max(speed_.y, minSpeed_);
    jump();
}

void player::Jumping::jump() {
    if (player().physics().isGrounded()) {
        constexpr float magicConst = 2500.f; // Magic number is tweaked experimentally
        player().physics().properties().velocity.y =
                -player().world.gravity * speed_.y / magicConst;
    }
}

void player::Jumping::adjustAnimationFPS() {
    const auto speedRatio = magnitudeRatio(speed_, player().physics().properties().velocity);
    auto &currentAnimation = player().getRenderManager().getMainSprite().getAnimator().getCurrentAnimation();
    currentAnimation.setSPF(1.f / static_cast<float>(currentAnimation.getFPR()) * speedRatio * 0.6f);
}
