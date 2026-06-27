#ifndef BONK_GAME_DEFAULT_CORE_HPP
#define BONK_GAME_DEFAULT_CORE_HPP

#include "Game/Engines/StateMachine/StateMachine.hpp"
#include "DefaultStateSet.hpp"
#include "Game/World/Entity/Actor/Player/Player.hpp"


namespace player {
    class Player;

    class DefaultCore final : public StateMachine::Core<DefaultStateSet> {
    public:
        explicit DefaultCore(Player& player);
    };
} // player

#endif //BONK_GAME_DEFAULT_CORE_HPP
