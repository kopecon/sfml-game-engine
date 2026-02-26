#ifndef BONK_GAME_JUMPING_HPP
#define BONK_GAME_JUMPING_HPP

#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultState.hpp"

namespace player {
    class Jumping final : public DefaultState {
    public:
        explicit Jumping(Player &player);

    private:
        void jump();
        void adjustAnimationFPS()override;
    };
}



#endif //BONK_GAME_JUMPING_HPP