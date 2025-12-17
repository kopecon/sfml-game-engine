//
// Created by Andrew on 08/12/2025.
//

#ifndef BONK_GAME_STATE_MACHINE_ENGINE_HPP
#define BONK_GAME_STATE_MACHINE_ENGINE_HPP
#include <assert.h>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>


template <typename Manager, typename StateSet>
class State {
protected:
    Manager *pManager{nullptr};
public:
    virtual ~State();
    State(Manager *pManager, const StateSet &stateID) :
    pManager(pManager),
    stateID(stateID)
    {}

    StateSet stateID{};
    State *pPreviousState{nullptr};

    virtual void onEnter() {}
    virtual void onExit() {}

    virtual void update() = 0;

    virtual StateSet next(const std::vector<StateSet> &conditions) = 0;
};


template<typename Manager, typename StateSet>
State<Manager, StateSet>::~State() = default;


template<typename Manager, typename StateSet>
class StateMachineEngine {
public:
    StateMachineEngine() = default;
    State<Manager, StateSet> *pCurrentState{nullptr};
    StateSet targetState{};  // Usually triggered by the user's input
    std::vector<StateSet> conditions{};
    // List of available states
    std::unordered_map<StateSet, std::unique_ptr<State<Manager, StateSet>>> states{};

    template<typename T>
    void addState(std::unique_ptr<T> state)
    requires std::is_base_of_v<State<Manager, StateSet>, T> {
        auto [it, inserted] = states.emplace(state->stateID, std::move(state));

        if (!pCurrentState && inserted) {
            pCurrentState = it->second.get();
        }
    }

    void act() const;
    void transition(const StateSet &stateID) {
        auto pNextState = states.at(stateID).get();
        pNextState->pPreviousState = pCurrentState;
        pCurrentState = pNextState;
    }
    void update();
};


template<typename Manager, typename StateSet>
void StateMachineEngine<Manager, StateSet>::act() const {
    if (pCurrentState != nullptr) pCurrentState->update();
}


template<typename Manager, typename StateSet>
void StateMachineEngine<Manager, StateSet>::update() {
    assert(pCurrentState != nullptr);
    pCurrentState->update();
    conditions.push_back(targetState);
    StateSet newState = pCurrentState->next(conditions);
    if (newState != pCurrentState->stateID) {
        transition(newState);
    }
}

#endif //BONK_GAME_STATE_MACHINE_ENGINE_HPP
