#ifndef BONK_GAME_PLAYER_STATE_HPP
#define BONK_GAME_PLAYER_STATE_HPP

#include "Utils/EnumSet.hpp"
#include "Game/Engines/StateMachine/State.hpp"


namespace player {
    class Player;

    template<EnumSetConcept StateSet>
    class PlayerState : public State<StateSet> {
    public:
        PlayerState(Player &target, const typename StateSet::ID &id)
            : State<StateSet>(target, id) {
        }

    protected:
        [[nodiscard]] Player &player() {
            return static_cast<Player &>(this->target_);
        }
        [[nodiscard]] const Player &player() const {
            return static_cast<const Player &>(this->target_);
        }
    };
} // player

#endif //BONK_GAME_PLAYER_STATE_HPP
