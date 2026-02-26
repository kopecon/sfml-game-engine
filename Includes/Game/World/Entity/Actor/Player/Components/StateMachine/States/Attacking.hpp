#ifndef BONK_GAME_ATTACKING_HPP
#define BONK_GAME_ATTACKING_HPP

#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultState.hpp"


namespace player {
    class Attacking final : public DefaultState {
    public:
        explicit Attacking(Player &player);

    private:
        eval::Conditioned exit_;
        void adjustAnimationFPS() override;
    };
}


#endif //BONK_GAME_ATTACKING_HPP
