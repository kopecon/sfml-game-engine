//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_WALKING_HPP
#define BONK_GAME_WALKING_HPP

#include "PlayerState.hpp"


namespace player {
    class Walking final : public PlayerState {
    public:
        explicit Walking(Player &player);
    };
}



#endif //BONK_GAME_WALKING_HPP