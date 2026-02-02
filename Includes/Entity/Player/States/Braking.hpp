//
// Created by Andrew on 01/02/2026.
//

#ifndef BONK_GAME_BRAKING_HPP
#define BONK_GAME_BRAKING_HPP
#include "PlayerState.hpp"

namespace player {
    class Braking final : public PlayerState {
    public:
        explicit Braking(Player& player);
    };
}


#endif //BONK_GAME_BRAKING_HPP