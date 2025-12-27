//
// Created by Andrew on 27/12/2025.
//

#include "../../../../Includes/Entity/Player/States/Winking.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Winking::Winking(Player *pPlayer): PlayerState(pPlayer, StateSet::ID::WINKING) {
    auto wetEyes = [pPlayer]{return pPlayer->eyeDryness <= 0;};
    addEdge(std::make_unique<Edge>(wetEyes, StateSet::ID::IDLE));
    addAction([pPlayer] {
        pPlayer->eyeDryness -= 1;
    });
}
