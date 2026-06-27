#include "Player/Player.hpp"

#include "Engine.hpp"


namespace player {
    Player::Player(const Engine &engine) : Actor(engine) {
        controls().setInput(engine.getInput());
        controls().loadBindings(Controls::defaultBindings);
    }
} // player
