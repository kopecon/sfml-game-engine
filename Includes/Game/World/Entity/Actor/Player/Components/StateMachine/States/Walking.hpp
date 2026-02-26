#ifndef BONK_GAME_WALKING_HPP
#define BONK_GAME_WALKING_HPP

#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultState.hpp"


namespace player {
    class Walking final : public DefaultState {
    public:
        explicit Walking(Player &player);

    private:
        MovementComponent &movement_;

        void onEnter(Context context) override;

        void walk();

        void adjustAnimationFPS() override;
    };
}


#endif //BONK_GAME_WALKING_HPP
