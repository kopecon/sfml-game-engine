#ifndef BONK_GAME_STOPPING_HPP
#define BONK_GAME_STOPPING_HPP

#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultState.hpp"


namespace player {
    class Stopping final : public DefaultState {
    public:
        explicit Stopping(Player &player);

    private:
        void setStateAnimation() override;
        void stop();
    };
}



#endif //BONK_GAME_STOPPING_HPP