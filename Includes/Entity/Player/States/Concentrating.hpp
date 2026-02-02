//
// Created by Andrew on 26/01/2026.
//

#ifndef BONK_GAME_CONCENTRATING_HPP
#define BONK_GAME_CONCENTRATING_HPP
#include "PlayerState.hpp"


namespace player {
    class Concentrating final : public PlayerState {
    public:
        explicit Concentrating(Player &player);

    private:
        Condition exit() const;
        Action changeColor() const;
        Action resetColor() const;
        Action levitate() const;
    };
} // player

#endif //BONK_GAME_CONCENTRATING_HPP