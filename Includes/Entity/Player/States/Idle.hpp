//
// Created by Andrew on 26/12/2025.
//

#ifndef BONK_GAME_IDLE_HPP
#define BONK_GAME_IDLE_HPP

#include "PlayerState.hpp"


namespace player {
    class Idle final : public PlayerState {
    public:
        explicit Idle(Player &player);

    private:
        [[nodiscard]] Action mainAction() const;
    };
}

#endif //BONK_GAME_IDLE_HPP