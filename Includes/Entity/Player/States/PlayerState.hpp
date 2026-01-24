//
// Created by Andrew on 27/12/2025.
//

#ifndef BONK_GAME_PLAYER_STATE_HPP
#define BONK_GAME_PLAYER_STATE_HPP
#include "StateSet.hpp"
#include "../../../Game/Engines/StateMachine/State.hpp"

namespace player {
    class Player;

    class PlayerState : public State<StateSet> {
    public:
        PlayerState(Player &player, const EnumSet<StateSet>::ID &stateID) :
            State(stateID),
            player_(player)
            {}
    protected:
        // REFERENCES
        Player &player_;
    };
}

#endif //BONK_GAME_PLAYER_STATE_HPP
