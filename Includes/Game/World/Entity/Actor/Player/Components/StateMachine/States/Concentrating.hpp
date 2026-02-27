#ifndef BONK_GAME_CONCENTRATING_HPP
#define BONK_GAME_CONCENTRATING_HPP

#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultState.hpp"


namespace player {
    class Concentrating final : public DefaultState {
    public:
        explicit Concentrating(Player &player);

    private:
        void changeColor();
        void resetColor();
    };
} // player

#endif //BONK_GAME_CONCENTRATING_HPP