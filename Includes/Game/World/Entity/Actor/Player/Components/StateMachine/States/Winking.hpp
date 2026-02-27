#ifndef BONK_GAME_WINKING_HPP
#define BONK_GAME_WINKING_HPP

#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultState.hpp"


namespace player {
    class Winking final : public DefaultState {
    public:
        explicit Winking(Player &player);

    private:
        void wink();
    };
}

#endif //BONK_GAME_WINKING_HPP
