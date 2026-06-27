#ifndef BONK_GAME_BRAKING_HPP
#define BONK_GAME_BRAKING_HPP

#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultState.hpp"


namespace player {
    class Braking final : public DefaultState {
    public:
        explicit Braking(Player& player);

    private:
        void brake();
    };
}


#endif //BONK_GAME_BRAKING_HPP