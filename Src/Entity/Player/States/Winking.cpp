//
// Created by Andrew on 27/12/2025.
//

#include "../../../../Includes/Entity/Player/States/Winking.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Winking::Winking(Player &player): PlayerState(player, StateSet::ID::WINKING) {
    // CONDITIONS
    auto wetEyes = [&player]{return player.getEyeDryness() <= 0;};
    addMainAction([&player] {player.setEyeDryness(player.getEyeDryness()-1);});
    addMainAction([&player] {player.getMovement().brake();});
    // EDGES
    makeEdge(wetEyes     , IDLE         );
    makeEdge(stop        , STOPPING     );
    makeEdge(jump        , JUMPING      );
    makeEdge(run         , RUNNING      );
    makeEdge(walk        , WALKING      );
    makeEdge(attack      , ATTACKING    );
    makeEdge(concentrate , CONCENTRATING);
}
