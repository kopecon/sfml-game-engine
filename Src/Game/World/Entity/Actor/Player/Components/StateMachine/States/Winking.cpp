#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Winking.hpp"
#include "Game/World/Entity/Actor/Player/Player.hpp"


player::Winking::Winking(Player &player): DefaultState(player, DefaultStateSet::ID::WINKING) {
    // CONDITIONS
    const auto wetEyes = eval::Conditioned([&player]{return player.getEyeDryness() <= 0;});
    // EDGES
    makeEdge(wetEyes     , IDLE         );
    makeEdge(jump_       , JUMPING      );
    makeEdge(run_        , RUNNING      );
    makeEdge(walk_       , WALKING      );
    makeEdge(attack_     , ATTACKING    );
    makeEdge(concentrate_, CONCENTRATING);
    // ACTIONS
    addAction(MAIN_ACTION(wink));
}

void player::Winking::wink() {
    this->player().setEyeDryness(this->player().getEyeDryness()-1);
}
