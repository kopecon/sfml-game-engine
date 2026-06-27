#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Attacking.hpp"
#include "Game/World/Entity/Actor/Player/Player.hpp"


player::Attacking::Attacking(Player &player)
    : DefaultState(player, DefaultStateSet::ID::ATTACKING),
      exit_(
          [this] {
              return this->player().getRenderManager().getMainSprite().getAnimator().getCurrentAnimation().getStatus()
              == AnimationStatus::FINISHED;
          }
      ) {
    // EDGES
    makeEdge(exit_, IDLE);
}

void player::Attacking::adjustAnimationFPS() {
    auto &currentAnimation = player().getRenderManager().getMainSprite().getAnimator().getCurrentAnimation();
    currentAnimation.setSPF(0.05f);
}
