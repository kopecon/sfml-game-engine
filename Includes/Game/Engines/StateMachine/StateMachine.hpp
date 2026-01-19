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

class Entity;


template<EnumSetConcept StateSet>
class StateMachine {
    bool verbose{false};
    void _enter(State<StateSet> &state) {
        pCurrentState = &state;
        pCurrentState->onEnter();
    }
    void _exit(State<StateSet> &state) {
        pCurrentState->onExit();
        pPreviousState = &state;
    }
    void _generateFallBackEdge(State<StateSet> &state) {
        state.addEdge(std::make_unique<typename State<StateSet>::Edge>(pCurrentState->ID));
        #ifndef NDEBUG
        std::cerr << "\nWarning: State "
                  << StateSet::name(state.ID)
                  << " has no edges. Auto-generated fallback to "
                  << StateSet::name(pCurrentState->ID)
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

    State<StateSet>& getState(typename StateSet::ID stateID) {
        auto it = states.find(stateID);
        if (it == states.end()) {
            if (verbose) std::cout << "Desired state " << StateSet::name(stateID) << " is not implemented!\n";
            return *pCurrentState;
        }
        return *it->second;
    }

    template<typename T>
    void addState(std::unique_ptr<T> pState)
    requires std::is_base_of_v<State<StateSet>, T> {

        auto [it, inserted] = states.try_emplace(pState->ID, std::move(pState));

        if (!pCurrentState && inserted) {
            pCurrentState = it->second.get();
        }
    }

    template<typename T, typename ... Args>
    State<StateSet>* createState(Args&&... args)
    requires std::is_base_of_v<State<StateSet>, T> {
        auto newState = std::make_unique<T>(std::forward<Args>(args)...);
        auto [it, inserted] = states.try_emplace(newState->ID, std::move(newState));
        if (!pCurrentState && inserted) {
            pCurrentState = it->second.get();
        }
        return it->second.get();
    }

    void transition() {
        auto newStateID = pCurrentState->next(desiredStateID);
        if (newStateID != pCurrentState->ID) {
            getState(newStateID); // No error
            auto &newState = getState(newStateID); //error
            if (!newState.hasEdges()) _generateFallBackEdge(newState);
            _exit(*pCurrentState);
            _enter(newState);
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