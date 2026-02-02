//
// Created by Andrew on 08/12/2025.
//

#ifndef BONK_GAME_STOPPING_HPP
#define BONK_GAME_STOPPING_HPP

#include "PlayerState.hpp"


namespace player {
    class Stopping final : public PlayerState {
    public:
        explicit Stopping(Player &player);
    };
}



#endif //BONK_GAME_STOPPING_HPP