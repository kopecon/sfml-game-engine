#include "Game/World/Entity/Player/Components/States/Stopping.hpp"
#include "Game/World/Entity/Player/Player.hpp"


player::Stopping::Stopping(Player &player): PlayerState(player, StateSet::ID::STOPPING) {
    // EDGES
    makeEdge(brake  , BRAKING  );
    makeEdge(stop   , STOPPING );
    makeEdge(jump   , JUMPING  );
    makeEdge(run    , RUNNING  );
    makeEdge(walk   , WALKING  );
    makeEdge(attack , ATTACKING);
    // ACTIONS
    addMainAction([&player]{player.getMovement().brake();});
}
