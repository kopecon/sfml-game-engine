//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_RUNNING_HPP
#define BONK_GAME_RUNNING_HPP
#include "../../../Game/Engines/StateMachine.hpp"


class Running final : public State<player::StateManager>{
public:
    explicit Running(player::StateManager *stateManager);

    void update() override;

    player::StateManager::States next(const std::vector<player::StateManager::States> &conditions) override;
};


#endif //BONK_GAME_RUNNING_HPP