//
// Created by Andrew on 26/12/2025.
//

#ifndef BONK_GAME_STATE_NEW_HPP
#define BONK_GAME_STATE_NEW_HPP

#include <iostream>


template<typename States>
class State_new final : public StateBase_new<States>{
    std::function<void()> updateFn{};
public:
#pragma region constructors
    explicit State_new(const States &stateID)
        : StateBase_new<States>(stateID) {
    }
#pragma endregion

    std::function<States (const std::vector<States> &)> nextFn{};

    void update() override {
        if (updateFn) {
            updateFn();
        }
        else {
            std::cout << "Update of " << static_cast<int>(this->stateID) << " state is not implemented\n";
        }
    }
};

#endif //BONK_GAME_STATE_NEW_HPP