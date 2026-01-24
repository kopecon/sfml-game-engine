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


template<EnumSetConcept StateSet>
class StateMachine {
public:
    #pragma region constructors
    StateMachine() = default;
    #pragma endregion

    // SETTERS
    void setDesiredState(const typename StateSet::ID id) {
        desiredStateID_ = id;
    }

    void setVerbose(bool value) {
        verbose_ = value;
        for (const auto &it : states_) {
            it.second.get()->verbose = value;
        }
    }

    // GETTERS
    [[nodiscard]] State<StateSet>& getCurrentState() {
        assert(pCurrentState_);
        return *pCurrentState_;
    }

    [[nodiscard]] const State<StateSet>& getCurrentState() const {
        // Read only return.
        assert(pCurrentState_);
        return *pCurrentState_;
    }

    [[nodiscard]] State<StateSet>& getPreviousState() {
        if (!pPreviousState_) return *pCurrentState_;
        return *pPreviousState_;
    }

    [[nodiscard]] const State<StateSet>& getPreviousState() const {
        // Read only return.
        if (!pPreviousState_) return *pCurrentState_;
        return *pPreviousState_;
    }


    State<StateSet>& getState(typename StateSet::ID stateID) {
        auto it = states_.find(stateID);
        if (it == states_.end()) {
            if (verbose_) std::cout << "Desired state " << StateSet::name(stateID) << " is not implemented!\n";
            return *pCurrentState_;
        }
        return *it->second;
    }

    template<typename T>
    void addState(std::unique_ptr<T> pState)
    requires std::is_base_of_v<State<StateSet>, T> {

        auto [it, inserted] = states_.try_emplace(pState->ID, std::move(pState));

        State<StateSet>* addedState = it->second.get();

        // Prevent mandatory null-checks
        if (!pCurrentState_ && inserted) {
            pCurrentState_ = addedState;
        }
    }

    template<typename T, typename ... Args>
    State<StateSet>* createState(Args&&... args)
    requires std::is_base_of_v<State<StateSet>, T> {
        auto newState = std::make_unique<T>(std::forward<Args>(args)...);
        auto [it, inserted] = states_.try_emplace(newState->getID(), std::move(newState));
        if (!pCurrentState_ && inserted) {
            pCurrentState_ = it->second.get();
        }
        return it->second.get();
    }

    // UPDATE
    void update() {
        // 1. Check if we are in a state
        assert(pCurrentState_);
        // // 2. Do state action
        pCurrentState_->update();
        // // 3. Transition to the new state
        transition();
    }
private:
    // MEMBERS
    std::unordered_map<typename StateSet::ID, std::unique_ptr<State<StateSet>>> states_{};
    State<StateSet> *pCurrentState_{nullptr};
    State<StateSet> *pPreviousState_{nullptr};
    typename StateSet::ID desiredStateID_{};
    // DEBUG SETTINGS
    bool verbose_{false};
    // ACTIONS
    void enter(State<StateSet> &state) {
        setCurrentState(state);
        getCurrentState().onEnter();
    }

    void exit(State<StateSet> &state) {
        getPreviousState().onExit();
        setPreviousState(state);
    }

    void transition() {
        auto newStateID = getCurrentState().next(desiredStateID_);
        if (newStateID != getCurrentState().getID()) {
            auto &newState = getState(newStateID);
            if (!newState.hasEdges()) generateFallBackEdge(newState);
            exit(*pCurrentState_);
            enter(newState);
        }
    }

    void generateFallBackEdge(State<StateSet> &state) {
        // Intended as a last resort to prevent stuck states
        state.addEdge(std::make_unique<typename State<StateSet>::Edge>(getCurrentState().getID()));
#ifndef NDEBUG
        std::cerr << "\nWarning: State "
                  << StateSet::name(state.getID())
                  << " has no edges. Auto-generated fallback to "
                  << StateSet::name(pCurrentState_->getID())
                  << '\n';
#endif
    }
    // SETTERS
    void setCurrentState(State<StateSet> &state) {
        if (states_.contains(state.getID())) {
            pCurrentState_ = &state;
        }
        else {
            std::cout << "Attempted to set nonexisting current state: "
            << StateSet::name(state.getID()) << "\n";
        }
    }

    void setPreviousState(State<StateSet> &state) {
        if (states_.contains(state.getID())) {
            pPreviousState_ = &state;
        }
        else {
            std::cout << "Attempted to set nonexisting previous state: "
            << StateSet::name(state.getID()) << "\n";
        }
    }
};

#endif //BONK_GAME_STATE_MACHINE_HPP