//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_JUMPING_HPP
#define BONK_GAME_JUMPING_HPP

#include "PlayerState.hpp"

namespace player {
    class Jumping final : public PlayerState {
    public:
        explicit Jumping(Player &player);
    };
}



#endif //BONK_GAME_JUMPING_HPP