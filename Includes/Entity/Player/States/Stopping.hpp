//
// Created by Andrew on 08/12/2025.
//

#ifndef BONK_GAME_STOPPING_HPP
#define BONK_GAME_STOPPING_HPP
#include "../../../Game/Engines/StateMachineEngine.hpp"


class Stopping final : public State<player::StateManager, player::States> {
public:
    explicit Stopping(player::StateManager *stateManager);

    void update() override;

    player::States next(const std::vector<player::States> &conditions) override;
};


#endif //BONK_GAME_STOPPING_HPP