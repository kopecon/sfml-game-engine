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
    StateMachine() {initWithNoneState();}
    #pragma endregion

    // ACTIONS
    template<typename T>
    T& addState(std::unique_ptr<T> state)
    requires std::is_base_of_v<State<StateSet>, T> {
        T& addedState = *state;
        auto [it, inserted] = states_.try_emplace(state->getID(), std::move(state));
        assert(inserted && "State ID already exists");
        bootstrap(addedState);
        return addedState;
    }

    template<typename T, typename ... Args>
    T& createState(Args&&... args)
    requires std::is_base_of_v<State<StateSet>, T> {
        auto createdState = std::make_unique<T>(std::forward<Args>(args)...);
        return addState(std::move(createdState));
    }

    // SETTERS
    void setDesiredState(const typename StateSet::ID id) {
        desiredStateID_ = id;
    }

    void setVerbose(bool value) {
        verbose_ = value;
        for (const auto &it : states_) {
            it.second.get()->setVerbose(value);
        }
    }

    // GETTERS
    [[nodiscard]] State<StateSet>& getCurrentState() {
        assert(pCurrentState_);  // Should not happen. Initiated with "none" state.
        return *pCurrentState_;
    }

    [[nodiscard]] const State<StateSet>& getCurrentState() const {
        // Read only return.
        assert(pCurrentState_);  // Should not happen. Initiated with "none" state.
        return *pCurrentState_;
    }

    [[nodiscard]] State<StateSet>& getPreviousState() {
        assert(pPreviousState_);  // Should not happen. Initiated with "none" state.
        return *pPreviousState_;
    }

    [[nodiscard]] const State<StateSet>& getPreviousState() const {
        // Read only return.
        assert(pPreviousState_);  // Should not happen. Initiated with "none" state.
        return *pPreviousState_;
    }

    // UPDATE
    void update() {
        transition();
        getCurrentState().update();
    }

private:
    // LIST OF ADDED STATES
    std::unordered_map<typename StateSet::ID, std::unique_ptr<State<StateSet>>> states_{};
    // ACCESS
    State<StateSet> *pCurrentState_{nullptr};
    State<StateSet> *pPreviousState_{nullptr};
    typename StateSet::ID desiredStateID_{};
    // SCAFFOLDING
    constexpr static StateSet::ID NONE{-1};  //TODO: Temporary.
    // DEBUG SETTINGS
    bool verbose_{false};

    // ACTIONS
    void enter(State<StateSet> &state) {
        state.onEnter();
        setCurrentState(state);
    }

    void exit(State<StateSet> &state) {
        state.onExit();
        setPreviousState(state);
    }

    void transition() {
        auto &currentState = getCurrentState();
        typename StateSet::ID nextStateID = currentState.getNext(desiredStateID_);
        if (nextStateID != currentState.getID()) {
            State<StateSet> &nextState = getNextState(nextStateID);
            if (!nextState.hasEdges()) generateFallBackEdge(nextState);
            exit(currentState);
            enter(nextState);
            desiredStateID_ = currentState.getID();
        }
    }

    void initWithNoneState() {
        auto noneCurrentState = std::make_unique<State<StateSet>>(NONE);
        auto [current_it, current_inserted] = states_.try_emplace(noneCurrentState->getID(), std::move(noneCurrentState));
        if (current_inserted) {
            pCurrentState_ = current_it->second.get();
            pPreviousState_ = current_it->second.get();
        }
    }
    void bootstrap(State<StateSet> &first) {
        // This is one-way connection that gets executed immediately.
            states_.at(NONE)->connect([]{return true;}, first);
    }

    void generateFallBackEdge(State<StateSet> &state) {
        // Intended as a last resort to prevent stuck states. Temporary solution. Implement better state graph validating.
        state.addEdge(std::make_unique<typename State<StateSet>::Edge>(getCurrentState().getID()));
        #ifndef NDEBUG
        std::cerr << "\nWarning: State "
                  << StateSet::name(state.getID())
                  << " has no edges. Auto-generated fallback to "
                  << StateSet::name(getCurrentState().getID())
                  << '\n';
        #endif
    }

    // SETTERS
    void setCurrentState(State<StateSet> &state) {
        if (states_.contains(state.getID())) {
            pCurrentState_ = &state;
        }
        else {
            std::cerr << "Attempted to set nonexisting current state: "
            << StateSet::name(state.getID()) << "\n";
        }
    }

    void setPreviousState(State<StateSet> &state) {
        if (states_.contains(state.getID())) {
            pPreviousState_ = &state;
        }
        else {
            std::cerr << "Attempted to set nonexisting previous state: "
            << StateSet::name(state.getID()) << "\n";
        }
    }

    // GETTERS
    State<StateSet>& getNextState(typename StateSet::ID stateID) {
        auto it = states_.find(stateID);
        if (it == states_.end()) {
            if (verbose_) std::cerr << "Desired state " << StateSet::name(stateID) << " is not implemented!\n";
            return getCurrentState();
        }
        return *it->second;
    }
};

#endif //BONK_GAME_STATE_MACHINE_HPP