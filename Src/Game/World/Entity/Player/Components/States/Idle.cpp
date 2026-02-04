#include "Game/World/Entity/Player/Components/States/Idle.hpp"
#include "Game/World/Entity/Player/Player.hpp"


using enum player::StateSet::ID;

player::Idle::Idle(Player &player) : PlayerState(player, IDLE) {
    // EDGES
    makeEdge(stop, STOPPING);
    makeEdge(run, RUNNING);
    makeEdge(walk, WALKING);
    makeEdge(jump, JUMPING);
    makeEdge(wink, WINKING);
    makeEdge(attack, ATTACKING);
    auto timeEval = std::make_unique<TimedEvaluation>(concentrate);
    auto timeEdge = std::make_unique<Edge>(getID(), std::move(timeEval), CONCENTRATING);
    addEdge(std::move(timeEdge));
    // ACTIONS
    addMainAction(mainAction());
}

Action player::Idle::mainAction() const {
    Player &player = player_;
    return [&player] {
        player.setEyeDryness(player.getEyeDryness() + 0.1f);
        player.getMovement().brake();
    };
}
