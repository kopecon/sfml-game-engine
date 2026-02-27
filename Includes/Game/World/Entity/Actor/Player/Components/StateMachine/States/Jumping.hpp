#ifndef BONK_GAME_JUMPING_HPP
#define BONK_GAME_JUMPING_HPP

#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultState.hpp"


namespace player {
    class Jumping final : public DefaultState {
    public:
        explicit Jumping(Player &player);

    private:
        float minSpeed_{300.f};
        sf::Vector2f speed_{0.f, minSpeed_};

        void onEnter(Context context) override;

        void jump();

        void adjustAnimationFPS() override;
    };
}


#endif //BONK_GAME_JUMPING_HPP
