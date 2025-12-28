#include "../../../../Includes/Entity/Player/States/Jumping.hpp"
#include "../../../../Includes/Entity/Player/Player.hpp"


player::Jumping::Jumping(Player *pPlayer): PlayerState(pPlayer, StateSet::ID::JUMPING) {
    using enum StateSet::ID;
    // Helpers
    // ReSharper disable once CppDFAUnreachableFunctionCall
    auto grounded = [this] {return this->pPlayer->physics.isGrounded();};
    // ReSharper disable once CppDFAUnreachableFunctionCall
    auto previous = [this] {
        const auto* prev = this->pPlayer->stateMachine.pPreviousState;
        return prev ? prev->stateID : NONE;
    };
    // Conditions
    auto walking  = [grounded, previous] {return grounded() && previous() == WALKING;};
    auto running  = [grounded, previous] {return grounded() && previous() == RUNNING;};
    // Edges
    addEdge(std::make_unique<Edge>(running,  RUNNING));
    addEdge(std::make_unique<Edge>(walking,  WALKING));
    addEdge(std::make_unique<Edge>(grounded, IDLE));
    addEdge(std::make_unique<Edge>(ATTACKING));
    // Actions
    addEnterAction([pPlayer]{pPlayer->movement.jump();});
}
