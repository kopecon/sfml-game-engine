//
// Created by Andrew on 08/12/2025.
//

#ifndef BONK_GAME_STATE_MACHINE_ENGINE_HPP
#define BONK_GAME_STATE_MACHINE_ENGINE_HPP
#include <memory>


template <typename Manager, typename StateSet>
class State {
protected:
    Manager *pManager{nullptr};
public:

    virtual ~State();

    State(Manager *pManager, const StateSet &state) :
    pManager(pManager),
    state(state)
    {}

    StateSet state{};

    template<typename T>
    void enter() {
        // std::cout << pStateManager->pPlayer->name << " Entering State: " << typeid(*this).name() << "\n";
        std::unique_ptr<T> next = std::make_unique<T>(pManager);
        pManager->state = next->state;
        pManager->pState = std::move(next);
    }

    virtual void act() = 0;

    virtual void exit() = 0;

};

template<typename Manager, typename StateSet>
State<Manager, StateSet>::~State() = default;


template<typename Manager, typename StateSet>
class StateMachineEngine {
public:

    std::unique_ptr<State<Manager, StateSet>> pState{nullptr};  // This refers to the actual state
    StateSet state{StateSet::IDLE};  // This just tags the current state so its "visible" to other modules
    StateSet targetState{};  // Usually triggered by the user's input

    void act() const;
    void update() const;
};

template<typename Manager, typename StateSet>
void StateMachineEngine<Manager, StateSet>::act() const {
    if (pState != nullptr) pState->act();
    // else std::cout << "Can't act on empty state pointer\n";
}

template<typename Manager, typename StateSet>
void StateMachineEngine<Manager, StateSet>::update() const {
    if (pState != nullptr) pState->exit(), act();
    // else std::cout << "Can't update empty state pointer\n";
}

#endif //BONK_GAME_STATE_MACHINE_ENGINE_HPP
