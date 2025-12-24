//
// Created by Andrew on 08/12/2025.
//

#ifndef BONK_GAME_STATE_MACHINE_ENGINE_HPP
#define BONK_GAME_STATE_MACHINE_ENGINE_HPP
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

#include "StateBase.hpp"


template<typename Manager>
class StateMachine {
    Manager *pManager{};
public:
    StateMachine() = default;
    explicit StateMachine(Manager *pManager) : pManager(pManager) {}

    StateBase<Manager> *pCurrentState{nullptr};
    typename Manager::States targetStateID{};  // Usually triggered by the user's input
    std::vector<typename Manager::States> conditions{};  // TODO for now the only condition inside the vector is just the desired state, in the future maybe other conditions would be added.
    // List of available states
    std::unordered_map<typename Manager::States, std::unique_ptr<StateBase<Manager>>> states{};


    template<typename T>
    void addState(T state)
    requires std::is_base_of_v<StateBase<Manager>, T> {
        auto pState = std::make_unique<T>(state);
        auto [it, inserted] = states.emplace(pState->stateID, std::move(pState));

        if (!pCurrentState && inserted) {
            pCurrentState = it->second.get();
        }
    }

    void act() const {
        if (pCurrentState != nullptr) pCurrentState->update();
    }

    void transition(const typename Manager::States &stateID) {
        auto it = states.find(stateID);
        if (it == states.end()) {
            std::cout << "Desired state " << static_cast<int>(stateID) << " not implemented!\n";
            return;
        }
        it->second->pPreviousState = pCurrentState;
        pCurrentState = it->second.get();
        pCurrentState->onEnter();
    }

    void update() {
        // 1. Check if we are in a state
        assert(pCurrentState != nullptr);
        // 2. Do state action
        pCurrentState->update();
        // 3. Update machine conditions
        conditions.clear();
        conditions.push_back(targetStateID);
        // 4. Transition to the new state
        auto newState = pCurrentState->next();
        if (newState != pCurrentState->stateID) {
            pCurrentState->onExit();
            transition(newState);
        }
    }
};

#endif //BONK_GAME_STATE_MACHINE_ENGINE_HPP
