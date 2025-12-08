//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_WALKING_HPP
#define BONK_GAME_WALKING_HPP
#include "State.hpp"


class Walking final : public State {
public:
    explicit Walking() : State(StateManager::States::WALKING) {}
    explicit Walking(StateManager *stateManager) : State(stateManager, StateManager::States::WALKING) {}

    void enter() override;

    void act() override;

    void exit(const StateManager::States &conditions) override;
};


#endif //BONK_GAME_WALKING_HPP