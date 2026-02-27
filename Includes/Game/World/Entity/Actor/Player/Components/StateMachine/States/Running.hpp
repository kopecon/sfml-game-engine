#ifndef BONK_GAME_RUNNING_HPP
#define BONK_GAME_RUNNING_HPP

#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultState.hpp"


namespace player {
    class Running final : public DefaultState {
    public:
        explicit Running(Player &player);

    private:
        sf::Vector2f speed_{400.f, 0.f};

        void run();

        void adjustAnimationFPS() override;
    };
}


#endif //BONK_GAME_RUNNING_HPP
