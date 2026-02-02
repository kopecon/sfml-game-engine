#include "Game/World/Entity/Player/Components/States/Walking.hpp"
#include "Game/World/Entity/Player/Player.hpp"


player::Walking::Walking(Player &player): PlayerState(player, StateSet::ID::WALKING) {
    // EDGES
    makeEdge(stop   , STOPPING );
    makeEdge(brake  , BRAKING  );
    makeEdge(jump   , JUMPING  );
    makeEdge(run    , RUNNING  );
    makeEdge(attack , ATTACKING);
    // ACTIONS
    const Action setDirection = [this] {
        if (input_.key(controls_.left).down) {
            player_.getMovement().setLeftWalkingDirection();
        }
        else {
            player_.getMovement().setRightWalkingDirection();
        }
    };
    addMainAction(setDirection);
    addMainAction([&player]{player.getMovement().walk();});
}
