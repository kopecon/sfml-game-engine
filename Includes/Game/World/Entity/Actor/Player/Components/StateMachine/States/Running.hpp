#ifndef BONK_GAME_RUNNING_HPP
#define BONK_GAME_RUNNING_HPP

#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultState.hpp"


namespace player {
    class Running final : public DefaultState {
    public:
        explicit Running(Player &player);

    private:
        MovementComponent &movement_;

        void onEnter(Context context) override;

        void run();

        void adjustAnimationFPS() override;
    };
}


#endif //BONK_GAME_RUNNING_HPP
