//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_RUNNING_HPP
#define BONK_GAME_RUNNING_HPP

#include "PlayerState.hpp"


namespace player {
    class Running final : public PlayerState {
    public:
        explicit Running(Player *pPlayer);
    };
}



#endif //BONK_GAME_RUNNING_HPP