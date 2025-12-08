//
// Created by Andrew on 08/12/2025.
//

#ifndef BONK_GAME_STOPPING_HPP
#define BONK_GAME_STOPPING_HPP
#include "State.hpp"


class Stopping final : public State {
public:
    explicit Stopping();

    explicit Stopping(StateManager *stateManager);

    void enter() override;

    void act() override;

    void exit(const StateManager::States &condition) override;
};


#endif //BONK_GAME_STOPPING_HPP