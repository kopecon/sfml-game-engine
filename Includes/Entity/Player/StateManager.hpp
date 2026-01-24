//
// Created by Andrew on 29/12/2025.
//

#ifndef BONK_GAME_STATE_MANAGER_HPP
#define BONK_GAME_STATE_MANAGER_HPP
#include "States/StateSet.hpp"
#include "../../Game/Engines/StateMachine/StateMachine.hpp"


namespace player {
    class Player;

    class StateManager {
    public:
        explicit StateManager(Player &player);
        // GETTERS
        [[nodiscard]] StateMachine<StateSet>& getEngine();
        [[nodiscard]] const StateMachine<StateSet>& getEngine() const;
        // UPDATE
        void update();

    private:
        // ENGINES
        StateMachine<StateSet> stateMachine_{};
    };
}


#endif //BONK_GAME_STATE_MANAGER_HPP