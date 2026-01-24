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
        assert(pPreviousState_);
        return *pCurrentState_;
    }
    [[nodiscard]] const State<StateSet>& getPreviousState() const {
        // Read only return.
        assert(pPreviousState_);
        return *pPreviousState_;
    }

    // LIST OF AVAILABLE STATES
    std::unordered_map<typename StateSet::ID, std::unique_ptr<State<StateSet>>> states{};
    // DEBUG SETTINGS

    void setVerbose(bool value) {
        verbose_ = value;
        for (const auto &it : states) {
            it.second.get()->verbose = value;
        }
    }

    State<StateSet>& getState(typename StateSet::ID stateID) {
        auto it = states.find(stateID);
        if (it == states.end()) {
            if (verbose_) std::cout << "Desired state " << StateSet::name(stateID) << " is not implemented!\n";
            return *pCurrentState_;
        }
        return *it->second;
    }

    template<typename T>
    void addState(std::unique_ptr<T> pState)
    requires std::is_base_of_v<State<StateSet>, T> {

        auto [it, inserted] = states.try_emplace(pState->ID, std::move(pState));

        // Prevent mandatory null-checks
        if (!pCurrentState_ && inserted) {
            pCurrentState_ = it->second.get();
        }
        // Prevent mandatory null-checks
        if (!pPreviousState_ && inserted) {
            pPreviousState_ = it->second.get();
        }
    }

    template<typename T, typename ... Args>
    State<StateSet>* createState(Args&&... args)
    requires std::is_base_of_v<State<StateSet>, T> {
        auto newState = std::make_unique<T>(std::forward<Args>(args)...);
        auto [it, inserted] = states.try_emplace(newState->getID(), std::move(newState));
        if (!pCurrentState_ && inserted) {
            pCurrentState_ = it->second.get();
        }
        return it->second.get();
    }

    void transition() {
        auto newStateID = pCurrentState_->next(desiredStateID_);
        if (newStateID != pCurrentState_->getID()) {
            getState(newStateID); // No error
            auto &newState = getState(newStateID); //error
            if (!newState.hasEdges()) generateFallBackEdge(newState);
            exit(*pCurrentState_);
            enter(newState);
        }
    }

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
    typename StateSet::ID desiredStateID_{};
    State<StateSet> *pCurrentState_{nullptr};
    State<StateSet> *pPreviousState_{nullptr};
    bool verbose_{false};

    void enter(State<StateSet> &state) {
        pCurrentState_ = &state;
        pCurrentState_->onEnter();
    }
    void exit(State<StateSet> &state) {
        pCurrentState_->onExit();
        pPreviousState_ = &state;
    }
    void generateFallBackEdge(State<StateSet> &state) {
        state.addEdge(std::make_unique<typename State<StateSet>::Edge>(pCurrentState_->getID()));
#ifndef NDEBUG
        std::cerr << "\nWarning: State "
                  << StateSet::name(state.getID())
                  << " has no edges. Auto-generated fallback to "
                  << StateSet::name(pCurrentState_->getID())
                  << '\n';
#endif
    }
};

#endif //BONK_GAME_STATE_MACHINE_HPP