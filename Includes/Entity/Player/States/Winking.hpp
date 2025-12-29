//
// Created by Andrew on 27/12/2025.
//

#ifndef BONK_GAME_WINKING_HPP
#define BONK_GAME_WINKING_HPP
#include "PlayerState.hpp"


namespace player {
    class Winking final : public PlayerState {
    public:
        explicit Winking(Player &player);
    };
}

#endif //BONK_GAME_WINKING_HPP
