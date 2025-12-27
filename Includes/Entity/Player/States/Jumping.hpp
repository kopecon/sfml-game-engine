//
// Created by Andrew on 07/12/2025.
//

#ifndef BONK_GAME_JUMPING_HPP
#define BONK_GAME_JUMPING_HPP

#include "../../../Game/Engines/StateMachine/State.hpp"
#include "../Player.hpp"
#include "StateSet.hpp"

namespace player {
    class Jumping final : public State<StateSet> {
    public:
        explicit Jumping(Player *pPlayer) : State(StateSet::ID::JUMPING), pPlayer(pPlayer) {
            // Helpers
            // ReSharper disable once CppDFAUnreachableFunctionCall
            auto grounded = [this] {return this->pPlayer->physics.isGrounded();};
            // ReSharper disable once CppDFAUnreachableFunctionCall
            auto previous = [this] {
                const auto* prev = this->pPlayer->stateMachine.pPreviousState;
                return prev ? prev->stateID : StateSet::ID::NONE;
            };

            // Conditions
            using enum StateSet::ID;
            auto idle    = [grounded, previous] {return grounded() && previous() == IDLE;};
            auto walking = [grounded, previous] {return grounded() && previous() == WALKING;};
            auto running = [grounded, previous] {return grounded() && previous() == RUNNING;};

            addEdge(std::make_unique<Edge>(idle   , IDLE   ));
            addEdge(std::make_unique<Edge>(walking, WALKING));
            addEdge(std::make_unique<Edge>(running, RUNNING));

            addEnterAction([pPlayer]{pPlayer->movement.jump();});
        }
        // HOST
        Player *pPlayer{nullptr};
    };
}



#endif //BONK_GAME_JUMPING_HPP