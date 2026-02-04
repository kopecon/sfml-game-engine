//
// Created by Andrew on 27/12/2025.
//

#ifndef BONK_GAME_PLAYER_STATE_HPP
#define BONK_GAME_PLAYER_STATE_HPP
#include "StateSet.hpp"
#include "Game/World/Entity/Player/Player.hpp"
#include "Game/Engines/StateMachine/State.hpp"


using enum player::StateSet::ID;


namespace player {
    class PlayerState : public State<StateSet> {
    public:
        PlayerState(Player &player, const EnumSet<StateSet>::ID &stateID) :
            State(stateID),
            player_(player),
            input_(player.getInput()),
            controls_(input_.getControls()) {
        }
    protected:
        // REFERENCES
        Player &player_;
        InputComponent& input_;
        Controls& controls_;
        // COMMON CONDITIONS
        Trigger idle = [this] { //TODO: temporary version
            if (std::abs(player_.velocity.x) <= 10.f) {
                return true;
            }
            return false;
        };
        Trigger brake = [this] {
            if (!input_.key(controls_.left).down && !input_.key(controls_.right).down) {
                return true;
            }
            return false;
        };
        Trigger walk = [this] {
            if (input_.key(controls_.left).down || input_.key(controls_.right).down) {
                return true;
            }
            return false;
        };
        Trigger run = [this] {
            if (input_.key(controls_.run).down) {
                return walk();
            }
            return false;
        };
        Trigger stop = [this] {
            if (input_.key(controls_.left).down && input_.key(controls_.right).down) {
                return true;
            }
            return false;
        };
        Trigger jump = [this] {
            if (input_.key(controls_.jump).down) {
                return true;
            }
            return false;
        };
        Trigger attack = [this] {
            if (input_.key(controls_.attack).pressed) {
                return true;
            }
            return false;
        };
        Trigger concentrate = [this] {
            if (input_.key(controls_.concentrate).pressed) {
                return true;
            }
            return false;
        };
        Trigger wink = [this] {
            if (player_.getEyeDryness() >= 100) {
                return true;
            }
            return false;
        };
    };
}

#endif //BONK_GAME_PLAYER_STATE_HPP
