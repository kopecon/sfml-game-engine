//
// Created by Andrew on 27/12/2025.
//

#ifndef BONK_GAME_ATTACKING_HPP
#define BONK_GAME_ATTACKING_HPP
#include "PlayerState.hpp"

namespace player {
    class Attacking final : public PlayerState {
    public:
        explicit Attacking(Player &player);

    private:
        Trigger idle_{};
    };
}


#endif //BONK_GAME_ATTACKING_HPP
