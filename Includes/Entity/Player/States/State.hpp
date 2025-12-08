//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_STATE_HPP
#define BONK_GAME_STATE_HPP
#include <iostream>
#include "StateManager.hpp"


class State {
protected:
    StateManager *pStateManager{nullptr};
public:
    virtual ~State();

    explicit State(StateManager *stateManager, const StateManager::States &state);

    StateManager::States state{};

    template<typename T>
    void enter() {
        // std::cout << pStateManager->pPlayer->name << " Entering State: " << typeid(*this).name() << "\n";
        std::unique_ptr<T> next = std::make_unique<T>(pStateManager);
        pStateManager->state = next->state;
        pStateManager->pState = std::move(next);
    }

    virtual void act() = 0;

    virtual void exit();
};

#endif //BONK_GAME_STATE_HPP
