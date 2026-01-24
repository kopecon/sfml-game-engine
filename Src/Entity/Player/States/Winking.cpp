//
// Created by Andrew on 27/12/2025.
//

#include "../../../../Includes/Entity/Player/States/Winking.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Winking::Winking(Player &player): PlayerState(player, StateSet::ID::WINKING) {
    auto wetEyes = [&player]{return player.getEyeDryness() <= 0;};
    addEdge(std::make_unique<Edge>(wetEyes, StateSet::ID::IDLE));
    addEdge(std::make_unique<Edge>(StateSet::ID::WALKING));
    addEdge(std::make_unique<Edge>(StateSet::ID::RUNNING));
    addEdge(std::make_unique<Edge>(StateSet::ID::JUMPING));
    addEdge(std::make_unique<Edge>(StateSet::ID::STOPPING));
    addAction([&player] {player.setEyeDryness(player.getEyeDryness()-1);});
    addAction([&player] {player.getMovement().brake();});
}
