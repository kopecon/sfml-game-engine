#ifndef BONK_GAME_IDLE_HPP
#define BONK_GAME_IDLE_HPP

#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultState.hpp"


namespace player {
    class Idle final : public DefaultState {
    public:
        explicit Idle(Player &player);

    private:
        void dryEyes();
    };
}

#endif //BONK_GAME_IDLE_HPP
