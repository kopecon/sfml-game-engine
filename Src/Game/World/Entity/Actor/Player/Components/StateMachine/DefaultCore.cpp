#include "Game/World/Entity/Actor/Player/Components/StateMachine/DefaultCore.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Idle.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Jumping.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Walking.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Running.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Attacking.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Concentrating.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Winking.hpp"
#include "Game/World/Entity/Actor/Player/Components/StateMachine/States/Braking.hpp"


namespace player {
    DefaultCore::DefaultCore(Player &player)
        : Core(static_cast<actor::Actor&>(player), std::make_unique<Idle>(player)) {
        createState<Jumping>(player);
        createState<Running>(player);
        createState<Walking>(player);
        createState<Braking>(player);
        createState<Winking>(player);
        createState<Attacking>(player);
        createState<Concentrating>(player);
    }
} // player
