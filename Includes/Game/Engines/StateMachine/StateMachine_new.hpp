//
// Created by Andrew on 08/12/2025.
//

#ifndef BONK_GAME_STATE_MACHINE_NEW_HPP
#define BONK_GAME_STATE_MACHINE_NEW_HPP
#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "StateBase_new.hpp"


template<typename States>
class StateMachine_new {
public:
    StateMachine_new() = default;

    StateBase_new<States> *pCurrentState{nullptr};
    StateBase_new<States> *pPreviousState{nullptr};
    States desiredStateID{};

    // List of available states
    std::unordered_map<States, std::unique_ptr<StateBase_new<States>>> states{};

    template<typename T>
    void addState(std::unique_ptr<T> pState)
    requires std::is_base_of_v<StateBase_new<States>, T> {

        auto [it, inserted] = states.emplace(pState->stateID, std::move(pState));

        if (!pCurrentState && inserted) {
            pCurrentState = it->second.get();
        }
    }

    void transition() {
        auto newState = pCurrentState->next(desiredStateID);
        if (newState != pCurrentState->stateID) {
            pCurrentState->onExit();

            auto it = states.find(newState);
            if (it == states.end()) {
                std::cout << "Desired state " << static_cast<int>(newState) << " not implemented!\n";
                return;
            }
            pPreviousState = pCurrentState;
            pCurrentState = it->second.get();
            pCurrentState->onEnter();
        }
    }

    void update() {
        // 1. Check if we are in a state
        assert(pCurrentState != nullptr);
        // 2. Do state action
        pCurrentState->update();
        // 3. Transition to the new state
        transition();
    }
};

#endif //BONK_GAME_STATE_MACHINE_NEW_HPP