//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_STATE_HPP
#define BONK_GAME_STATE_HPP
#include <string>
#include "StateManager.hpp"

class Player;


class State {
protected:
    StateManager *pStateManager{nullptr};
public:
    virtual ~State();
    explicit State(const StateManager::States &state);
    explicit State(StateManager *stateManager, const StateManager::States &state);

    StateManager::States state{};

    virtual void enter();

    virtual void act() = 0;

    virtual void exit(const StateManager::States &condition);
};

#endif //BONK_GAME_STATE_HPP
