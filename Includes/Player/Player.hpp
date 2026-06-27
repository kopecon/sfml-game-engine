#pragma once

#include "StateMachine/Actor/Actor.hpp"


namespace player {
    class Player : public Actor {
    public:
        explicit Player(const Engine &engine);
    };
} // player
