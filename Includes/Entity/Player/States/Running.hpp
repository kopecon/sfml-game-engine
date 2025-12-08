//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_RUNNING_HPP
#define BONK_GAME_RUNNING_HPP
#include "State.hpp"


class Running final : public State{
public:
    explicit Running();

    explicit Running(StateManager *stateManager);

    void enter() override;

    void act() override;

    void exit(const StateManager::States &condition) override;
};


#endif //BONK_GAME_RUNNING_HPP