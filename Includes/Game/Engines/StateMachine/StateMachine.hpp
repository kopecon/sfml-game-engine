//
// Created by Andrew on 08/12/2025.
//

#ifndef BONK_GAME_STATE_MACHINE_HPP
#define BONK_GAME_STATE_MACHINE_HPP
#include <cassert>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "State.hpp"


template<StateSetConcept StateSet>
class StateMachine {
    bool verbose{false};
    void _enter(State<StateSet> *pState) {
        pCurrentState = pState;
        pCurrentState->onEnter();
    }
    void _exit(State<StateSet> *pState) {
        pCurrentState->onExit();
        pPreviousState = pState;
    }
    void _generateFallBackEdge(State<StateSet> *pState) {
        pState->addEdge(std::make_unique<typename State<StateSet>::Edge>(pCurrentState->stateID));
#ifndef NDEBUG
        std::cerr << "\nWarning: State "
                  << StateSet::name(pState->stateID)
                  << " has no edges. Auto-generated fallback to "
                  << StateSet::name(pCurrentState->stateID)
                  << '\n';
#endif
    }
public:
    #pragma region constructors
    StateMachine() = default;

    explicit StateMachine(Entity *pEntity) : pEntity(pEntity){}
    #pragma endregion

    // HOST
    Entity *pEntity{nullptr};
    // STATE ACCESS
    State<StateSet> *pCurrentState{nullptr};
    State<StateSet> *pPreviousState{nullptr};
    typename StateSet::ID desiredStateID{};
    // LIST OF AVAILABLE STATES
    std::unordered_map<typename StateSet::ID, std::unique_ptr<State<StateSet>>> states{};
    // DEBUG SETTINGS

    void setVerbose() {
        verbose = true;
        for (const auto &it : states) {
            it.second.get()->verbose = true;
        }
    }
    void resetVerbose() {
        verbose = false;
        for (const auto &it : states) {
            it.second.get()->verbose = false;
        }
    }

    State<StateSet>* getState(typename StateSet::ID stateID) {
        auto it = states.find(stateID);
        if (it == states.end()) {
            if (verbose) std::cout << "Desired state " << StateSet::name(stateID) << " is not implemented!\n";
            return nullptr;
        }
        return it->second.get();
    }

    template<typename T>
    void addState(std::unique_ptr<T> pState)
    requires std::is_base_of_v<State<StateSet>, T> {

        auto [it, inserted] = states.emplace(pState->stateID, std::move(pState));

        if (!pCurrentState && inserted) {
            pCurrentState = it->second.get();
        }
    }

    void transition() {
        auto newStateID = pCurrentState->next(desiredStateID);
        if (newStateID != pCurrentState->stateID) {
            if (const auto newState = getState(newStateID)) {
                if (!newState->hasEdges()) _generateFallBackEdge(newState);
                _exit(pCurrentState);
                _enter(newState);
            }
        }
    }

    void update() {
        // 1. Check if we are in a state
        assert(pCurrentState != nullptr);
        // // 2. Do state action
        pCurrentState->update();
        // // 3. Transition to the new state
        transition();
    }
};

#endif //BONK_GAME_STATE_MACHINE_HPP