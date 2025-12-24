//
// Created by Andrew on 24/12/2025.
//

#ifndef BONK_GAME_STATE_HPP
#define BONK_GAME_STATE_HPP

#include "StateBase.hpp"
#include <iostream>


template<typename Manager>
class State final : public StateBase<Manager>{
    std::function<void()> updateFn{};
public:
    #pragma region constructors
    State(Manager *pManager, const typename Manager::States &stateID)
        : StateBase<Manager>(pManager, stateID) {
    }
    #pragma endregion

    std::function<typename Manager::States (const std::vector<typename Manager::States> &)> nextFn{};

    void update() override {
        if (updateFn) {
            updateFn();
        }
        else {
            std::cout << "Update of " << static_cast<int>(this->stateID) << " state is not implemented\n";
        }
    }
};


#endif //BONK_GAME_STATE_HPP